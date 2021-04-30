FROM ubuntu:20.04

# Basic Setup and Requirements
RUN apt-get update --fix-missing
RUN apt-get install -y locales && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Berlin
RUN apt-get install -y git build-essential cmake zlib1g-dev libboost-program-options-dev libm4ri-dev libgmp-dev libmpfr-dev libmpc-dev tar unzip curl ocaml-interp ocaml-findlib menhir opam libapron-ocaml python3 python3-pip
RUN rm -rf /var/lib/apt/lists/*

# CryptoMiniSat (Version 5.8.0) & ApproxMC (Commit Tag 618b35b)
RUN git clone https://github.com/msoos/cryptominisat && cd cryptominisat && git checkout 5.8.0 && mkdir build && cd build && cmake .. && make && make install && cd ../..
RUN git clone https://github.com/meelgroup/approxmc/ && cd approxmc && git checkout 618b35b && mkdir build && cd build && cmake .. && make && make install && cd ../../


# GANAK (Commit Tag 33f36bc)
RUN git clone https://github.com/meelgroup/ganak.git && cd ganak && git checkout 33f36bc && mkdir build && cd build && cmake .. && make && cp ganak ../bin/ && cd ../bin && export PATH=$PATH:`pwd` && cd ../../

# Probab Analyzer (Commit Tag 0997eb4 with minor fix)
RUN opam init --disable-sandboxing && eval $(opam env) && opam install -y ounit && opam install -y apron && opam install -y bddapron && opam install -y zarith
RUN curl -k https://www.math.ucdavis.edu/\~latte/software/packages/binary/latte-integrale-1.6-x86_64-unknown-linux-gnu.zip > latte.zip
RUN mkdir latte && unzip latte.zip -d latte
RUN git clone https://github.com/aleksdimovski/probab_analyzer.git && cd probab_analyzer && git checkout 0997eb4
# Repair Probab Analyzer through minor fixes
RUN rm -f /probab_analyzer/banal/banal_rat.ml && rm -f /probab_analyzer/Main.native
COPY dimovski-fix/banal_rat.ml /probab_analyzer/banal/banal_rat.ml
COPY dimovski-fix/compile.sh /probab_analyzer/compile.sh
RUN cd /probab_analyzer && chmod u+x compile.sh && ./compile.sh
COPY dimovski-fix/compile.sh compile.sh
RUN pwd
RUN chmod u+x compile.sh

# counterSharp (Commit Tag ae04135)
RUN curl https://www.cprover.org/cbmc/download/cbmc-5-11-linux-64.tgz > cbmc.tar.gz && mkdir /cbmc && tar -xzvf cbmc.tar.gz -C /cbmc
RUN git clone https://github.com/samysweb/counterSharp.git && cd counterSharp && pip3 install --no-cache-dir -r requirements.txt

RUN curl http://fmv.jku.at/runlim/runlim-1.10.tar.gz > runlim.tar.gz && mkdir runlim && tar -xzvf runlim.tar.gz -C runlim && cd runlim/runlim-1.10 && ./configure.sh && make && cd ../../

# Add scripts
ADD ./scripts /scripts

ENV PATH="${PATH}:/ADDMC:/ganak/bin:/runlim/runlim-1.10:/latte/bin:/probab_analyzer:/experiments:/cbmc:/scripts"
ENV PYTHONPATH="${PYTHONPATH}:/counterSharp"

RUN mkdir /experiments && mkdir /experiments/benchmarks && mkdir /experiments/benchmarks-dimovski && mkdir /experiments/logParsing
ADD ./cwd /experiments
ADD ./benchmarks /experiments/benchmarks
ADD ./benchmarks-dimovski /experiments/benchmarks-dimovski
ADD ./logParsing /experiments/logParsing
ADD README.md /experiments/README.txt
ADD LICENSE.txt /experiments

WORKDIR /experiments

ENTRYPOINT [ "/bin/bash" ]