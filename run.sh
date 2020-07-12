#! /bin/bash

# Sample for second argument: --function=testfun --unwind 1

inputFile=`pwd`/benchmarks/$1
resultDir=`pwd`/results/$1

echo $resultDir

if [ ! -f $inputFile ]; then
    echo "File not found!"
	exit
fi

if [ -d $resultDir ]; then
	echo "Result directory already exists"
	exit
fi

mkdir -p $resultDir

{
echo "** Experiment Repository **"
git --no-pager show --pretty=short --shortstat
git --no-pager status

echo "** CounterSharp Repository **"
cd ../counterSharp
git --no-pager show --pretty=short --shortstat
git --no-pager status
} > $resultDir/init.log 2>&1

{
echo "** counterSharp **"
echo "** counterSharp **" >&2
chrt -b 0 runlim -r 14400 -s 2048 python -m counterSharp --amm $resultDir/amm.dimacs --amh $resultDir/amh.dimacs --asm $resultDir/asm.dimacs --ash $resultDir/ash.dimacs -d $2 $inputFile
echo "** AMM **"
echo "** AMM **" >&2
chrt -b 0 runlim -r 14400 -s 2048 approxmc --sparse 1 $resultDir/amm.dimacs
echo "** AMH **"
echo "** AMH **" >&2
chrt -b 0 runlim -r 14400 -s 2048 approxmc --sparse 1 $resultDir/amh.dimacs
echo "** ASM **"
echo "** ASM **" >&2
chrt -b 0 runlim -r 14400 -s 2048 approxmc --sparse 1 $resultDir/asm.dimacs
echo "** ASH **"
echo "** ASH **" >&2
chrt -b 0 runlim -r 14400 -s 2048 approxmc --sparse 1 $resultDir/ash.dimacs
} > $resultDir/stdout.log 2> $resultDir/stderr.log