#! /bin/bash
CUR_DIR=`pwd`
exec_bench(){
	if [ `hostname` = "hal9000" ]; then
		HOMEPATH=/home/steuber
		TMPDIR=/tmp/experiment
	else
		HOMEPATH=/home/i12/steuber
		TMPDIR=/tmp/docker-steuber/experiment
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

	

		
	# Sample for second argument: --function=testfun --unwind 1
	for num in 01 02 03 04 05; do
		resultDir=$resultDirOverall/$num/counterSharp

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
		echo "******* Experiment Repository *******"
		git --no-pager show --pretty=short --shortstat
		git --no-pager status

		echo "******* CounterSharp Repository *******"
		cd ../counterSharp
		git --no-pager show --pretty=short --shortstat
		git --no-pager status
		} > $resultDir/init.log 2>&1

		{
		eval chrt -b 0 runlim -r 900 -s 2048 python3 -m counterSharp --amm $resultDir/amm.dimacs --amh $resultDir/amh.dimacs --asm $resultDir/asm.dimacs --ash $resultDir/ash.dimacs --con $resultDir/con.dimacs -d $2 $inputFile
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
