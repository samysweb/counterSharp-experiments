from os import listdir
from os.path import join, isdir, exists
import sys

from statistics import median

class BenchmarkToolRun:
	def __init__(self,benchmarkParam,toolParam):
		self.benchmark=benchmarkParam
		self.tool=toolParam
	def printMedian(self, timeList,status):
		isOK = False
		isMO = False
		isTO = False
		timesConsidered=[]
		for t,s in zip(timeList,status):
			if s=="ok":
				isOK = True
				timesConsidered.append(t)
			elif s=="time":
				isTO = True
			elif s=="memory":
				isMO = True
			else:
				print("?")
				print("% [parser] unknown status "+str(s))
				return
		if isOK:
			print(median(timesConsidered),end="")
			if isMO or isTO:
				print("*",end="")
		else:
			if isTO and isMO:
				print("TO/MO",end="")
			elif isTO:
				print("TO",end="")
			elif isMO:
				print("MO",end="")

		
		


class SingleBenchmarkToolRun(BenchmarkToolRun):
	COLNUM=1
	def __init__(self,benchmarkParam,toolParam):
		super(SingleBenchmarkToolRun,self).__init__(benchmarkParam,toolParam)
		self.empty=True
		self.time = []
		self.mem = []
		self.status = []
		self.res = []
		for run in range(1,6):
			stderrPath = join(self.benchmark,"0"+str(run),self.tool,"stderr.log")
			if not exists(stderrPath):
				print("[parser] Cannot find file %s"%(str(stderrPath)),file=sys.stderr)
				continue
			print("[parser] Parsing %s"%(str(stderrPath)),file=sys.stderr)
			self.empty=False
			with open(stderrPath,"r") as stderr:
				for line in stderr:
					if line.startswith("[runlim] status:"):
						self.status.append(line.split()[-1].strip())
					elif line.startswith("[runlim] real:"):
						self.time.append(float(line.split()[-2].strip()))
					elif line.startswith("[runlim] space:"):
						self.mem.append(float(line.split()[-2].strip()))
			if self.tool == "dimovski" and self.status[-1]=="ok":
				with open(join(self.benchmark,"0"+str(run),self.tool,"stdout.log"),"r") as stdout:
					for line in stdout:
						if line.startswith("PROBABLITY OF SATISFACTION:"):
							exSucc = True
							succ = float(line.split()[-2].strip())
						elif line.startswith("PROBABLITY OF VIOLATION:"):
							exViol = True
							viol = float(line.split()[-2].strip())
						elif line.startswith("APPROX. PROBABLITY OF SATISFACTION BETWEEN:"):
							exSucc = False
							succ = (float(line.split()[-5].strip()),float(line.split()[-2].strip()))
						elif line.startswith("APPROX. PROBABLITY OF VIOLATION BETWEEN:"):
							exViol = False
							viol = (float(line.split()[-5].strip()),float(line.split()[-2].strip()))
				self.res.append((exSucc,exViol,succ,viol))
	def printHeader1(self):
		print("\multirow{2}{*}{%s}"%(self.tool),end="")
	def printHeader2(self):
		print("",end="")
	def printTimeData(self):
		self.printMedian(self.time,self.status)
			


			
		

class MultiBenchmarkToolRun(BenchmarkToolRun):
	COLNUM=5
	def __init__(self,benchmarkParam,toolParam):
		super(MultiBenchmarkToolRun,self).__init__(benchmarkParam,toolParam)
		self.empty=True
		self.time = {
			"CON":[],
			"AMM":[],
			"AMH":[],
			"ASM":[],
			"ASH":[]
		}
		self.mem = {
			"CON":[],
			"AMM":[],
			"AMH":[],
			"ASM":[],
			"ASH":[]
		}
		self.status = {
			"CON":[],
			"AMM":[],
			"AMH":[],
			"ASM":[],
			"ASH":[]
		}
		self.res = {
			"CON":[],
			"AMM":[],
			"AMH":[],
			"ASM":[],
			"ASH":[]
		}
		for run in range(1,6):
			stderrPath = join(self.benchmark,"0"+str(run),self.tool,"stderr.log")
			if not exists(stderrPath):
				print("[parser] Cannot find file %s"%(str(stderrPath)),file=sys.stderr)
				continue
			print("[parser] Parsing %s"%(str(stderrPath)),file=sys.stderr)
			self.empty=False
			curKey=""
			with open(stderrPath,"r") as stderr:
				for line in stderr:
					if line.startswith("** "):
						curKey = line.split()[1].strip()
					elif line.startswith("[runlim] status:"):
						self.status[curKey].append(line.split()[-1].strip())
					elif line.startswith("[runlim] real:"):
						self.time[curKey].append(float(line.split()[-2].strip()))
					elif line.startswith("[runlim] space:"):
						self.mem[curKey].append(float(line.split()[-2].strip()))
				with open(join(self.benchmark,"0"+str(run),self.tool,"stdout.log"),"r") as stdout:
					for line in stdout:
						if line.startswith("** "):
							curKey = line.split()[1].strip()
						if self.status[curKey][-1]=="ok":
							if line.startswith("s mc ") or line.startswith("s pmc "):
								self.res[curKey].append(line.split()[-1].strip())
	def printHeader1(self):
			print("\multicolumn{5}{c|}{%s}"%(self.tool),end="")
	def printHeader2(self):
		print("CON&\\amm&\\amh&\\asm&\\ash",end="")
	def printTimeData(self):
		self.printMedian(self.time["CON"],self.status["CON"])
		print("&",end="")
		self.printMedian(self.time["AMM"],self.status["AMM"])
		print("&",end="")
		self.printMedian(self.time["AMH"],self.status["AMH"])
		print("&",end="")
		self.printMedian(self.time["ASM"],self.status["ASM"])
		print("&",end="")
		self.printMedian(self.time["ASH"],self.status["ASH"])
	

TOOLS = {
	"counterSharp":SingleBenchmarkToolRun,
	"dimovski":SingleBenchmarkToolRun,
	"approxmc": MultiBenchmarkToolRun,
	"ganak": MultiBenchmarkToolRun
}


def aggergateData(basepath):
	benchmarks = [(f,join(basepath,f)) for f in listdir(basepath) if isdir(join(basepath,f))]
	data = {}
	for benchmark,benchmarkDir in benchmarks:
		data[benchmark] = {}
		for tool in TOOLS.keys():
			data[benchmark][tool]=TOOLS[tool](benchmarkDir,tool)
	return data

	

def timeTable(data):
	print("% Generating time table")
	numCols = 1
	for tool in TOOLS:
		numCols+=TOOLS[tool].COLNUM
	print("% Columns needed: "+str(numCols))
	key1 = list(data.keys())[0]
	print("\multirow{2}{*}{}",end="")
	for tool in TOOLS.keys():
		print("&",end="")
		data[key1][tool].printHeader1()
	print("\\\\")
	for tool in TOOLS.keys():
		print("&",end="")
		data[key1][tool].printHeader2()
	print("\\\\")
	for bench in data.keys():
		print(bench.split("/")[-1],end="")
		for tool in TOOLS.keys():
			print("&",end="")
			data[bench][tool].printTimeData()
		print("\\\\")



if __name__ == '__main__':
	data=aggergateData(sys.argv[1])
	if sys.argv[2] == "time":
		timeTable(data)