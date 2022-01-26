import csv
import copy
import shutil
import sys

with open('counts.csv', newline='') as csvfile:
	countreader = csv.reader(csvfile, delimiter=',')
	isFirst=True
	for row in countreader:
		if isFirst:
			print(",".join(row))
			isFirst=False
			continue
		newrow = copy.deepcopy(row)
		newrow[0]=row[0].replace("/","-")
		shutil.copy(sys.argv[1]+"/"+row[0], sys.argv[2]+"/"+newrow[0])
		print(','.join(newrow))