#! /bin/bash
IFS=","
echo $1
while read bench args; do
	echo $bench
	./run-instance.sh $bench "$args"
done < $1