# counterSharp Experiments
This repository contains the experiments of the [counterSharp Tool](https://github.com/samysweb/counterSharp).
- **Benchmarks** are contained in the folder `benchmarks` which also includes an overview on the sources and modifications to the benchmarks
- **Benchmark Results** are contained in the folder `results` in which all logs from benchmark runs reside. The logs are split-up by benchmark instance (first level folder) and run number (second level folder)
- **Log summarization** is possible through the python script in `logParsing/parse.py`
- **Running benchmarks**:
	- Run counterSharp on the benchmarks: `./run-counterSharp.sh instances.csv`

## Experiments to run
Model Counting competition: https://mccompetition.org/assets/files/2020/MC2020_awards.pdf
- [ ] CBMC results
- [ ] ApproxMC
- [ ] #SAT
	- (Shared) first place in MC 2020 [GANAK](https://github.com/meelgroup/ganak)
- [ ] Weighted #SAT which tool?
	- (Shared) first place in MC 2020 [ADDMC](https://github.com/vardigroup/ADDMC)?
- [ ] Tool by Dimovski et al.