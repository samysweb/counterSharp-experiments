#! /bin/bash

rm -rf ./results/
mkdir results

docker-compose run benchmarking run-counterSharp instances.csv
docker-compose run benchmarking run-approxmc instances.csv
docker-compose run benchmarking run-ganak instances.csv
docker-compose run benchmarking run-dimovski instances-dimovski.csv