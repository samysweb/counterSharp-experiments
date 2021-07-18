# `counterSharp` Experiment and Play Environment

This repository contains the reproducible experimental evaluation of the [counterSharp tool](https://github.com/samysweb/counterSharp).
The repository contains a Docker file which configures the counterSharp tool, two model counters (ApproxMC and Ganak) as well as the [tool by Dimovski et al.](https://github.com/aleksdimovski/probab_analyzer) for our experiments.
Furthermore the repository contains the benchmarks on which we ran our experiments as well as the logs of our experiments and scripts for transforming the log files into LaTeX tables.

This repository belongs to our publication at QEST 2021 ([BibTeX](https://teuber.dev/publication/countersharp2021/cite.bib)) and our evaluated artifact available [here](https://publikationen.bibliothek.kit.edu/1000134169).

## Getting Started

In order to pull and run the docker container execute the following line. It opens a shell allowing the execution of further commands:

```bash
docker run -it -v `pwd`/results:/experiments/results samweb/countersharp-experiments
```

By using a volume, the results are written to the host system rather than the docker container. 
You can remove the volume mounting option (`-v ...`), and create `/experiments/results` inside the container if you can spare the results.
If you are using the volume and run into permission problems, then you need to give rights via SELinux: `chcon -Rt svirt_sandbox_file_t `pwd`/results`.

| :exclamation:  This will create a writable folder `results` in your current folder which will hold any logs from experiments.  |
|--------------------------------------------------------------------------------------------------------------------------------|

A minimal example can be executed by running (this takes approximately **70 seconds**):
```bash
./showcase.sh
```
This will create benchmark log files for the benchmarks `for_bounded_loop1.c` and `overflow.c` in the folder [`results`](results).
For example, `/experiments/results/for_bounded_loop1.c/0X/` contains five folder for the five repeated runs of the experiments on this file. 
Each folder `/experiments/results/for_bounded_loop1.c/0X/` contains the folders for the different tools, which includes the log and output files.


A full run can be executed by running (this takes approximately a little under **2 days**):
```bash
./run-all.sh
```

Additionally single benchmarks can be executed through the following commands:
```bash
run-instance approx program.c "[counterSharp arguments]" # Runs countersharp with ApproxMC on program.c
run-instance ganak program.c "[counterSharp arguments]" # Runs countersharp with Ganak on program.c
Probab.native -single -domain polyhedra program.c # Runs the tool by Dimovski et al. for deterministic programs
Probab.native -single -domain polyhedra -nondet program.c # Runs the tool by Dimovski et al. for nondeterministic programs
```
For example we can execute `run-instance approx /experiments/benchmarks/confidence.c "--function testfun --unwind 1"` to obtain the outcome of counterSharp and ApproxMC for the benchmark `confidence.c`.
Note that the time information produced by runlim is always only for one part of the entire execution (i.e. for counterSharp or  one ApproxMC run or one Ganak run). The script `run-instance` is straightforwarded, we have the call to our tool [counterSharp](https://github.com/samysweb/counterSharp):

```bash
python3 -m counterSharp --amm /tmp/amm.dimacs --amh /tmp/amh.dimacs --asm /tmp/asm.dimacs --ash /tmp/ash.dimacs --con /tmp/con.dimacs -d $3 $2
```
which is followed by the call of `ApproxMC` oder `ganak`.



## Benchmarks
The benchmarks are contained in the folder [`benchmarks`](benchmarks) which also includes an overview on the sources and modifications to the benchmarks  
Note that benchmark versions for the tool by Dimovski et al. are contained in folder [`benchmarks-dimovski`](benchmarks-dimovski)

## Benchmark Results
The results are contained in the folder [`results`](results) in which all logs from benchmark runs reside.
The log files from the evaluation are not available in the Docker Image, but just on GitHub.
The logs are split-up by benchmark instance (first level folder), run number (second level folder) and tool (third level folder)  
For example, the file `results/bwd_loop1a.c/01/approxmc/stdout.log` contains the stdout and stderr of running approxmc on the instance `bwd_loop1a.c` in run `01`  

### Machine Details
All runs were executed on a Linux machine housing an Intel(R) Core(TM) i5-6500 CPU (3.20GHz) and 16GB of memory.
Note that for every benchmark log `01/counterSharp/init.log` contains information on the machine used for benchmark execution as well as on the commits used in the experiments.

## Running benchmarks
For all cases of automated benchmark execution we assume a CSV file containing relevant information on the instances to run: The first column is the benchmark's name, the second column are parameters passed to counterSharp (see `instances.csv`) or the tool by Dimovski (see `instances-dimovski.csv`).
All scripts produce benchmarking results for "missing" instances, i.e. instances for which no folder can be found in the `results` folder.

- Run counterSharp on the benchmarks:  
`run-counterSharp instances.csv`
- Run [ApproxMC](https://github.com/meelgroup/ApproxMC) on benchmarks:  
`run-approxmc instances.csv`
	- Only after counterSharp has been run
- Run [GANAK](https://github.com/meelgroup/ganak) on benchmarks:  
`run-ganak instances.csv`
	- Only after counterSharp has been run
- Run [Dimovski's tool](https://github.com/aleksdimovski/probab_analyzer) on benchmarks:  
`run-dimovski instances-dimovski.csv`

## Log summarization
Summarization is possible through the python script in `logParsing/parse.py` within the container.
The script takes as input a list of benchmarks to process and returns (parts of) a LaTeX table.
Note, that there must exist logs for all benchmarks provided in the CSV file for the call to succeed!
- **To obtain (sorted) results for deterministic benchmarks:**  
`cat logParsing/deterministic-sorted.csv| python3 logParsing/parse.py results aggregate2`
- **To obtain (sorted) results for nondeterministic benchmarks:**  
`cat logParsing/nondeterministic-sorted.csv| python3 logParsing/parse.py results nondet`

## Building the docker container
All tools are packaged into a Dockerfile which makes any installation unnecessary.
There is, however, the need for a running Docker installation.
The `Dockerfile` build depends on the accessibility of the following GitHub Repositories:
- [CryptoMiniSat](https://github.com/msoos/cryptominisat)
- [ApproxMC](https://github.com/meelgroup/approxmc)
- [Ganak](https://github.com/meelgroup/ganak)
- [Probab_Analyzer](https://github.com/aleksdimovski/probab_analyzer)
- [counterSharp](https://github.com/samysweb/counterSharp)
 
The Docker image is hosted at [Dockerhub](https://hub.docker.com/repository/docker/samweb/countersharp-experiments).

