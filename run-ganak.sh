#! /bin/bash
CUR_DIR=`pwd`
exec_bench(){
	if [ `hostname` = "hal9000" ]; then
		TMPDIR=/tmp/experiment
	else
		TMPDIR=/tmp/steuber/experiment
	fi

	mkdir -p $TMPDIR

	cd $CUR_DIR

	inputFile=`pwd`/benchmarks/$1
	if [ ! -f $inputFile ]; then
		echo "File $inputFile not found!"
		exit
	fi

	resultDirOverall=`pwd`/results/$1
	mkdir -p $resultDirOverall
	chmod -R a+rw $resultDirOverall
	


		
	# Sample for second argument: --function=testfun --unwind 1
	for num in 01 02 03 04 05; do
		dataDir=$resultDirOverall/$num/counterSharp
		resultDir=$resultDirOverall/$num/ganak

		if [ -d $resultDir ]; then
			echo "Result directory already exists, skipping"
			continue;
		fi
		mkdir -p $resultDir
		rm -rf $TMPDIR/*
		outputDir=$resultDir
		resultDir=$TMPDIR
		
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
		cd $CUR_DIR
		echo "******* Experiment Repository *******"
		git --no-pager show --pretty=short --shortstat
		git --no-pager status

		echo "******* CounterSharp Repository *******"
		cd ../counterSharp
		git --no-pager show --pretty=short --shortstat
		git --no-pager status
		} > $resultDir/init.log 2>&1

		{
		echo "** CON **"
		echo "** CON **" >&2
		chrt -b 0 runlim -r 300 -s 2048 ganak -t 300 -cs 1024 -seed $num $dataDir/con.dimacs
		echo "** AMM **"
		echo "** AMM **" >&2
		chrt -b 0 runlim -r 300 -s 2048 ganak -t 300 -cs 1024 -seed $num $dataDir/amm.dimacs
		echo "** AMH **"
		echo "** AMH **" >&2
		chrt -b 0 runlim -r 300 -s 2048 ganak -t 300 -cs 1024 -seed $num $dataDir/amh.dimacs
		echo "** ASM **"
		echo "** ASM **" >&2
		chrt -b 0 runlim -r 300 -s 2048 ganak -t 300 -cs 1024 -seed $num $dataDir/asm.dimacs
		echo "** ASH **"
		echo "** ASH **" >&2
		chrt -b 0 runlim -r 300 -s 2048 ganak -t 300 -cs 1024 -seed $num $dataDir/ash.dimacs
		} > $resultDir/stdout.log 2> $resultDir/stderr.log

		cp $resultDir/* $outputDir

		chmod -R a+rw $outputDir
	done
}


IFS=","
echo $1
while read bench args; do
	echo $bench
	exec_bench $bench "$args"
done < $1