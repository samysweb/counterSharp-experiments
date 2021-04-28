# counterSharp Experiments
This repository contains the reproducible experimental evaluation of the [counterSharp tool](https://github.com/samysweb/counterSharp).
The repository contains a Docker file which configures the counterSharp tool, two model counters (ApproxMC and Ganak) as well as the [tool by Dimovski et al.](https://github.com/aleksdimovski/probab_analyzer) for our experiments.
Furthermore the repository contains the benchmarks on which we ran our experiments as well as the logs of our experiments and scripts for transforming the log files into LaTex tables.

## Requirements & Installation
All tools are packaged into a Dockerfile which makes any installation unnecessary.
There is, however, the need for a running Docker installation including the `docker-compose` command.
The Dockerfile build depends on the accessability of the following GitHub Repositories:
- [CryptoMiniSat](https://github.com/msoos/cryptominisat)
- [ApproxMC](https://github.com/meelgroup/approxmc)
- [Ganak](https://github.com/meelgroup/ganak)
- [Probab_Analyzer](https://github.com/aleksdimovski/probab_analyzer)
- [counterSharp](https://github.com/samysweb/counterSharp)

The repository needs to be mountable by Docker and the `results` folder needs to be writbaly mountable by Docker

## Getting Started
First we need to pull the Docker container which can be done through the following command:
```
docker-compose pull
```

| :exclamation:  Any of the following commands will overwrite the benchmark results contained in [`results`](results)  |
|----------------------------------------------------------------------------------------------------------------------|

A minimal example can be executed by running (this takes approximately **70 seconds**):
```
./showcase.sh
```
This will create remove and recreate benchmark log files for the benchmarks `for_bounded_loop1.c` and `overflow.c` in the folder [`results`](results).

A full run can be executed by running (this takes approximately a little under **2 days**):
```
./run-all.sh
```

## Benchmarks
The benchmarks are contained in the folder [`benchmarks`](benchmarks) which also includes an overview on the sources and modifications to the benchmarks  
Note that benchmark versions for the tool by Dimovski et al. are contained in folder [`benchmarks-dimovski`](benchmarks-dimovski)

## Benchmark Results
The results are contained in the folder [`results`](results) in which all logs from benchmark runs reside. The logs are split-up by benchmark instance (first level folder), run number (second level folder) and tool (third level folder)  
For example, the file `results/bwd_loop1a.c/01/approxmc/stdout.log` contains the stdout out running approxmc on the instance `bwd_loop1a.c` in run `01`  
Note that `01/counterSharp/init.log` contains information on the machine used for benchmark execution as well as on the commits used in the experiments.

### Machine Details

## Running benchmarks
For all cases we assume a CSV file containing relevant information on the instances to run: The first column is the benchmark's name, the second column are parameters passed to counterSharp (see `instances.csv`) or the tool by Dimovski (see `instances-dimovski.csv`).
All scripts produce benchmarking results for "missing" instances, i.e. instances for which no benchmarking results can be found in the `results` folder.

- Run counterSharp on the benchmarks:  
`docker-compose run benchmarking run-counterSharp instances.csv`
- Run [ApproxMC](https://github.com/meelgroup/ApproxMC) on benchmarks:  
`docker-compose run benchmarking run-approxmc instances.csv`
	- Only after counterSharp has been run
- Run [GANAK](https://github.com/meelgroup/ganak) on benchmarks:  
`docker-compose run benchmarking run-ganak instances.csv`
	- Only after counterSharp has been run
- Run [Dimovski's tool](https://github.com/aleksdimovski/probab_analyzer) on benchmarks:  
`docker-compose run benchmarking run-dimovski instances-dimovski.csv`

## Log summarization
Summarization is possible through the python script in `logParsing/parse.py`.
The script requires a standard Python 3 installation.
The script takes as input a list of benchmarks to process and returns (parts of) a LaTex table:
- **To obtain (sorted) results for deterministic benchmarks:**  
`cat logParsing/deterministic-sorted.csv| python logParsing/parse.py results aggregate2`
- **To obtain (sorted) results for nondeterministic benchmarks:**  
`cat logParsing/nondeterministic-sorted.csv| python logParsing/parse.py results nondet`