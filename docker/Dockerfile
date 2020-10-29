FROM ubuntu:20.04

RUN apt-get update

RUN apt-get install -y locales && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Berlin

# ApproxMC
RUN apt-get install -y git build-essential cmake zlib1g-dev libboost-program-options-dev libm4ri-dev
RUN git clone https://github.com/msoos/cryptominisat && cd cryptominisat && git checkout 5.8.0 && mkdir build && cd build && cmake .. && make && make install && cd ../..
RUN apt-get install -y libgmp-dev
RUN git clone https://github.com/meelgroup/approxmc/ && cd approxmc && git checkout 4.0.1 && mkdir build && cd build && cmake .. && make && make install && cd ../../


# GANAK
RUN apt-get install -y libmpfr-dev libmpc-dev
RUN git clone https://github.com/meelgroup/ganak.git && cd ganak && git checkout 33f36bc && mkdir build && cd build && cmake .. && make && cp ganak ../bin/ && cd ../bin && export PATH=$PATH:`pwd` && cd ../../

# # ADDMC
RUN apt-get install -y autoconf tar unzip
RUN git clone https://github.com/vardigroup/ADDMC.git && cd ADDMC && git checkout mc-2020 && ./INSTALL.sh && export PATH=$PATH:`pwd` && cd ../

# # Probab Analyzer
RUN apt-get install -y curl ocaml-interp ocaml-findlib menhir opam
# RUN opam install ounit && opam install apron && opam install bddapron && opam install zarith
# RUN curl https://www.math.ucdavis.edu/~latte/software/packages/binary/latte-integrale-1.6-x86_64-unknown-linux-gnu.zip > latte.zip & mkdir latte && unzip latte.zip -d latte

RUN rm -rf /var/lib/apt/lists/*

RUN curl http://fmv.jku.at/runlim/runlim-1.10.tar.gz > runlim.tar.gz && mkdir runlim && tar -xzvf runlim.tar.gz -C runlim && cd runlim/runlim-1.10 && ./configure.sh && make && cd ../../


ENV PATH="${PATH}:/ADDMC:/ganak/bin:/runlim/runlim-1.10:/experiments"

RUN mkdir /experiments
WORKDIR /experiments