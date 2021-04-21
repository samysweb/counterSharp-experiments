#! /bin/bash

# Remove directories
rm -rf ./results/for_bounded_loop1.c
rm -rf ./results/overflow.c

docker-compose run benchmarking run-counterSharp showcase.csv
docker-compose run benchmarking run-approxmc showcase.csv
docker-compose run benchmarking run-ganak showcase.csv
docker-compose run benchmarking run-dimovski showcase-dimovski.csv