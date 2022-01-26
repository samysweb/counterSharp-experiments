# The counterSharp Model Counting benchmark family

A summary of all relevant information on this benchmark set can be found in the abstract (see abstract.pdf)

## counts.txt
This CSV file contains information on previously obtained counting results for all benchmarks.
In particular, the file contains (in this order):
- The file name
- The status of GANAK
- The count GANAK returned (if status is `ok`)
- The time GANAK took (if status is `ok`)
- The status of ApproxMC
- The count ApproxMC returned (is status is `ok`)
- The time ApproxMC took (if status is `ok`)

The status can either be `ok` or `fail` which signifies timeouts, memouts or other issues.
All information on the experimental setup can be found in the QEST 2021 paper "Quantifying Software Reliability via Model-Counting".

## checksums.txt
The checksums for all dimacs files were generated using the following command:
```bash
find *.dimacs -type f -exec sha256sum {} \;
```