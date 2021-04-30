#! /bin/bash

echo "Writing logs to ./results/..."

run-counterSharp instances.csv
run-approxmc instances.csv
run-ganak instances.csv
run-dimovski instances-dimovski.csv