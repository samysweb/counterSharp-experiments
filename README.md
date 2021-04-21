# counterSharp Experiments
This repository contains experiments run on the [counterSharp Tool](https://github.com/samysweb/counterSharp).

## Requirements & Installation
All tools are packaged into a Dockerfile which makes any installation unnecessary.
There is, however, the need for a running Docker installation including the `docker-compose` command.
The repository needs to be mountable by Docker and the results folder needs to be writbaly mountable by Docker

## Getting Started
First we need to build the Docker container which can be done through the following command:
```
docker-compose build
```

| :exclamation:  Any of the following commands will overwrite the benchmark results contained in [`results`](results)  |
|----------------------------------------------------------------------------------------------------------------------|

A minimal example can be executed by running:
```
./showcase.sh
```
This will create remove and recreate benchmark log files for the benchmarks `bwd_loop1a.c`, `bwd_loop1a-2.c`, `bwd_loop2.c`, `bwd_loop2-2.c`, `bwd_loop7.c` and `floor.c` in the folder [`results`](results).

A full run can be executed by running:
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
The script takes as input a list of benchmarks to process and returns (parts of) a LaTex table:
- **To obtain (sorted) results for deterministic benchmarks:**  
`cat deterministic-sorted.csv| python parse.py ../results aggregate2`
- **To obtain (sorted) results for nondeterministic benchmarks:**  
`cat nondeterministic-sorted.csv| python parse.py ../results nondet`