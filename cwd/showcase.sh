#! /bin/bash

echo "Writing logs to ./results/for_bounded_loop1.c and ./results/overflow.c...."

run-counterSharp showcase.csv
run-approxmc showcase.csv
run-ganak showcase.csv
run-dimovski showcase-dimovski.csv