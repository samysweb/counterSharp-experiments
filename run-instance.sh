#! /bin/bash

HOMEPATH=/home/steuber

inputFile=`pwd`/benchmarks/$1
if [ ! -f $inputFile ]; then
	echo "File not found!"
	exit
fi

resultDirOverall=`pwd`/results/$1
mkdir -p $resultDirOverall


	
# Sample for second argument: --function=testfun --unwind 1
for num in $(seq -w 01 05); do
	resultDir=$resultDirOverall/$num

	if [ -d $resultDir ]; then
		echo "Result directory already exists, skipping"
		continue;
	fi

	mkdir -p $resultDir
	
	{
	echo "******* Machine details *******"
	echo "$ hostname"
	hostname
	echo "$ lscpu"
	lscpu
	echo "$ cat /proc/meminfo"
	cat /proc/meminfo
	echo "$ cat /proc/version"
	cat /proc/version
	echo "$ lsblk"
	lsblk
	echo "******* Experiment Repository *******"
	git --no-pager show --pretty=short --shortstat
	git --no-pager status

	echo "******* CounterSharp Repository *******"
	cd ../counterSharp
	git --no-pager show --pretty=short --shortstat
	git --no-pager status
	} > $resultDir/init.log 2>&1

	{
	echo "** counterSharp **"
	echo "** counterSharp **" >&2
	source $HOMEPATH/anaconda3/etc/profile.d/conda.sh
	conda activate FP
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

	chmod -R a+rw $resultDir
done