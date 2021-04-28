from os import listdir
from os.path import join, isdir, exists
import sys

from statistics import median

class BenchmarkToolRun:
	def __init__(self,benchmarkParam,toolParam):
		self.benchmark=benchmarkParam
		self.tool=toolParam
	
	def getMedian(self, timeList, status):
		if self.empty:
			return False, False, False, 0
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
		if len(timesConsidered)==0:
			return False, isMO, isTO, 0
		return (isOK, isMO, isTO, median(timesConsidered))
	
	def getTotalTimeMedian(self):
		pass

	def printMedian(self, timeList,status):
		isOK, isMO, isTO, medianVal = self.getMedian(timeList, status)
		if isOK:
			print(medianVal,end="")
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
			# print("[parser] Parsing %s"%(str(stderrPath)),file=sys.stderr)
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
	def sum(self):
		return sum(self.time)
	def printHeader1(self):
		print("\multirow{2}{*}{%s}"%(self.tool),end="")
	def printHeader2(self):
		print("",end="")
	def printTimeData(self):
		self.printMedian(self.time,self.status)
	def getTotalTimeMedian(self):
		return self.getMedian(self.time, self.status)
			


			
		

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
			# print("[parser] Parsing %s"%(str(stderrPath)),file=sys.stderr)
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
	def sum(self):
		result = 0.0
		for k in self.time.keys():
			result+=sum(self.time[k])
		return result
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
	def getTotalTimeMedian(self):
		conOK, conMO, conTO, conT = self.getMedian(self.time["CON"], self.status["CON"])
		ammOK, ammMO, ammTO, ammT = self.getMedian(self.time["AMM"], self.status["AMM"])
		amhOK, amhMO, amhTO, amhT = self.getMedian(self.time["AMH"], self.status["AMH"])
		asmOK, asmMO, asmTO, asmT = self.getMedian(self.time["ASM"], self.status["ASM"])
		ashOK, ashMO, ashTO, ashT = self.getMedian(self.time["ASH"], self.status["ASH"])
		return (
			conOK and ammOK and amhOK and asmOK and ashOK,
			conMO or ammMO or amhMO or asmMO or ashMO,
			conTO or ammTO or amhTO or asmTO or ashTO,
			conT + ammT + amhT + asmT + ashT)
	def minASHASM(self):
		asmOK, asmMO, asmTO, asmT = self.getMedian(self.time["ASM"], self.status["ASM"])
		ashOK, ashMO, ashTO, ashT = self.getMedian(self.time["ASH"], self.status["ASH"])
		return (
			asmOK or ashOK,
			asmMO and ashMO,
			asmTO and ashTO,
			min([ashT,asmT])
		)
	def maxASHASM(self):
		asmOK, asmMO, asmTO, asmT = self.getMedian(self.time["ASM"], self.status["ASM"])
		ashOK, ashMO, ashTO, ashT = self.getMedian(self.time["ASH"], self.status["ASH"])
		return (
			asmOK and ashOK,
			asmMO or ashMO,
			asmTO or ashTO,
			max([ashT,asmT])
		)
	
	def getNonDetExact(self):
		ammOK, ammMO, ammTO, ammT = self.getMedian(self.time["AMM"], self.status["AMM"])
		amhOK, amhMO, amhTO, amhT = self.getMedian(self.time["AMH"], self.status["AMH"])
		asmOK, asmMO, asmTO, asmT = self.getMedian(self.time["ASM"], self.status["ASM"])
		ashOK, ashMO, ashTO, ashT = self.getMedian(self.time["ASH"], self.status["ASH"])
		return (
			(ammOK or amhOK) and (asmOK and ashOK),
			(ammMO and amhMO) or (asmMO or ashMO),
			(ammTO and amhTO) or (asmTO or ashTO),
			max([min([ammT,amhT]),max([asmT,ashT])]))
	
	def getNonDetApprox(self):
		ammOK, ammMO, ammTO, ammT = self.getMedian(self.time["AMM"], self.status["AMM"])
		amhOK, amhMO, amhTO, amhT = self.getMedian(self.time["AMH"], self.status["AMH"])
		asmOK, asmMO, asmTO, asmT = self.getMedian(self.time["ASM"], self.status["ASM"])
		ashOK, ashMO, ashTO, ashT = self.getMedian(self.time["ASH"], self.status["ASH"])
		return (
			(ammOK and amhOK) and (asmOK and ashOK),
			(ammMO or amhMO) or (asmMO or ashMO),
			(ammTO or amhTO) or (asmTO or ashTO),
			max([max([ammT,amhT]),max([asmT,ashT])]))
	

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
		print(bench.split("/")[-1].replace("_","\\_"),end="")
		for tool in TOOLS.keys():
			print("&",end="")
			data[bench][tool].printTimeData()
		print("\\\\")

def getAggregateTime(data):
	print("% Colums needed: 4")
	for bench in data.keys():
		print(bench.split("/")[-1].replace("_","\\_"),end="")
		counterOK,counterMO,counterTO, counterT = data[bench]["counterSharp"].getTotalTimeMedian()
		approxOK, approxMO, approxTO, approxT = data[bench]["approxmc"].getTotalTimeMedian()
		ganakOK, ganakMO, ganakTO, ganakT = data[bench]["ganak"].getTotalTimeMedian()
		dimovskiOK, dimovskiMO, dimovskiTO, dimovskiT = data[bench]["dimovski"].getTotalTimeMedian()
		print("&",end="")
		if counterOK and approxOK:
			smallest=True
			if dimovskiOK and counterT+approxT > dimovskiT:
				smallest=False
			elif counterOK and ganakOK and counterT+approxT > counterT+ganakT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(counterT+approxT)+"}",end="")
			else:
				print(counterT+approxT,end="")
		elif counterMO or approxMO:
			print("MO",end="")
		elif counterTO or approxTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("&",end="")
		if counterOK and ganakOK:
			smallest=True
			if dimovskiOK and counterT+ganakT > dimovskiT:
				smallest=False
			elif counterOK and approxOK and counterT+approxT < counterT+ganakT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(counterT+ganakT)+"}",end="")
			else:
				print(counterT+ganakT,end="")
		elif counterMO or ganakMO:
			print("MO",end="")
		elif counterTO or ganakTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("&",end="")
		if dimovskiOK:
			smallest=True
			if counterOK and approxOK and counterT+approxT < dimovskiT:
				smallest=False
			elif counterOK and ganakOK and counterT+ganakT < dimovskiT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(dimovskiT)+"}",end="")
			else:
				print(dimovskiT,end="")
		elif dimovskiMO:
			print("MO",end="")
		elif dimovskiTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("\\\\")

def getSensibleAggregate(data):
	"""
	Compute Time (/Space:)
	- Dimovski/Dimovski
	- CounterSharp+min(ganakASH,ganakASM) (/ max(CounterSharp, ganakASH+ganakASM))
	- CounterSharp+max(approxASH,approxASM) (/ max(CounterSharp, approxASH+approxASM))
	"""
	print("% Colums needed: 4")
	for rawline in sys.stdin:
		line = rawline.rstrip()
		print(line.replace("_","\\_"),end=" & ")
		dimovskiOK, dimovskiMO, dimovskiTO, dimovskiT = data[line]["dimovski"].getTotalTimeMedian()
		counterOK,counterMO,counterTO, counterT = data[line]["counterSharp"].getTotalTimeMedian()
		ganakOK, ganakMO, ganakTO, ganakT = data[line]["ganak"].minASHASM()
		approxOK, approxMO, approxTO, approxT = data[line]["approxmc"].maxASHASM()
		if dimovskiOK:
			smallest=True
			if counterOK and approxOK and counterT+approxT < dimovskiT:
				smallest=False
			elif counterOK and ganakOK and counterT+ganakT < dimovskiT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(round(dimovskiT,2))+"}",end="")
			else:
				print(dimovskiT,end="")
		elif dimovskiMO:
			print("MO",end="")
		elif dimovskiTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("&",end="")
		if counterOK and ganakOK:
			smallest=True
			if dimovskiOK and counterT+ganakT > dimovskiT:
				smallest=False
			elif counterOK and approxOK and counterT+approxT < counterT+ganakT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(round(counterT+ganakT,2))+"}",end="")
			else:
				print(counterT+ganakT,end="")
		elif counterMO or ganakMO:
			print("MO",end="")
		elif counterTO or ganakTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("&",end="")
		if counterOK and approxOK:
			smallest=True
			if dimovskiOK and counterT+approxT > dimovskiT:
				smallest=False
			elif counterOK and ganakOK and counterT+approxT > counterT+ganakT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(round(counterT+approxT,2))+"}",end="")
			else:
				print(counterT+approxT,end="")
		elif counterMO or approxMO:
			print("MO",end="")
		elif counterTO or approxTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("\\\\")

def getSensibleAggregateNondet(data):
	"""
	Compute Time (/Space:)
	- Dimovski/Dimovski
	- CounterSharp+min(ganakASH,ganakASM) (/ max(CounterSharp, ganakASH+ganakASM))
	- CounterSharp+max(approxASH,approxASM) (/ max(CounterSharp, approxASH+approxASM))
	"""
	print("% Colums needed: 4")
	for rawline in sys.stdin:
		line = rawline.rstrip()
		print(line.replace("_","\\_"),end=" & ")
		dimovskiOK, dimovskiMO, dimovskiTO, dimovskiT = data[line]["dimovski"].getTotalTimeMedian()
		counterOK,counterMO,counterTO, counterT = data[line]["counterSharp"].getTotalTimeMedian()
		ganakOK, ganakMO, ganakTO, ganakT = data[line]["ganak"].getNonDetExact()
		approxOK, approxMO, approxTO, approxT = data[line]["approxmc"].getNonDetApprox()
		if dimovskiOK:
			smallest=True
			if counterOK and approxOK and counterT+approxT < dimovskiT:
				smallest=False
			elif counterOK and ganakOK and counterT+ganakT < dimovskiT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(round(dimovskiT,2))+"}",end="")
			else:
				print(dimovskiT,end="")
		elif dimovskiMO:
			print("MO",end="")
		elif dimovskiTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("&",end="")
		if counterOK and ganakOK:
			smallest=True
			if dimovskiOK and counterT+ganakT > dimovskiT:
				smallest=False
			elif counterOK and approxOK and counterT+approxT < counterT+ganakT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(round(counterT+ganakT,2))+"}",end="")
			else:
				print(counterT+ganakT,end="")
		elif counterMO or ganakMO:
			print("MO",end="")
		elif counterTO or ganakTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("&",end="")
		if counterOK and approxOK:
			smallest=True
			if dimovskiOK and counterT+approxT > dimovskiT:
				smallest=False
			elif counterOK and ganakOK and counterT+approxT > counterT+ganakT:
				smallest=False
			if smallest:
				print("\\textbf{"+str(round(counterT+approxT,2))+"}",end="")
			else:
				print(counterT+approxT,end="")
		elif counterMO or approxMO:
			print("MO",end="")
		elif counterTO or approxTO:
			print("TO",end="")
		else:
			print("---", end="")
		print("\\\\")
	
def getSum(data):
	result=0.0
	for bench in data.keys():
		for tool in data[bench].keys():
			result+=data[bench][tool].sum()
	print(f"Total time: {result}s")



if __name__ == '__main__':
	data=aggergateData(sys.argv[1])
	if sys.argv[2] == "time":
		timeTable(data)
	elif sys.argv[2] == "aggregatetime":
		getAggregateTime(data)
	elif sys.argv[2] == "aggregate2":
		getSensibleAggregate(data)
	elif sys.argv[2] == "nondet":
		getSensibleAggregateNondet(data)
	elif sys.argv[2] == "sum":
		getSum(data)