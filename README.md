# counterSharp Experiments
This repository contains the experiments of the [counterSharp Tool](https://github.com/samysweb/counterSharp).
- **Benchmarks** are contained in the folder `benchmarks` which also includes an overview on the sources and modifications to the benchmarks
- **Benchmark Results** are contained in the folder `results` in which all logs from benchmark runs reside. The logs are split-up by benchmark instance (first level folder) and run number (second level folder)
- **Log summarization** is possible through the python script in `logParsing/parse.py`
- **Running benchmarks** works by either running a specific benchmark instance from the `benchmarks` folder through `./run-instance.sh <instance> "<additional args to countersharp>"` or by running `./run.sh <csv list of instances like instances.csv>`