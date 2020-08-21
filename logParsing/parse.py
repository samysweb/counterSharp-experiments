# YES, this is extremely hacky and no well written code...
from os import listdir
from os.path import join,isdir
import sys

from statistics import median

basepath = sys.argv[1]

instanceDirs = [join(basepath,f) for f in listdir(basepath) if isdir(join(basepath, f))]
#print(instanceDirs)
print("instance counterMem counterTime ammMem ammTime amhMem amhTime asmMem asmTime ashMem ashTime | amm | amh | asm | ash")
for instance in instanceDirs:
	amm = []
	amh = []
	asm = []
	ash = []
	ammT = []
	amhT = []
	asmT = []
	ashT = []
	ammM = []
	amhM = []
	asmM = []
	ashM = []
	counterT = []
	counterM = []
	for run in range(1,6):
		with open(join(instance,"0"+str(run),"stdout.log"),"r") as stdout:
			for line in stdout:
				if line.startswith("** AMM"):
					done=False
					for line in stdout:
						if line.startswith("c [appmc] Number of solutions is:"):
							amm.append(line.split(" ")[-1].strip())
							done=True
							break
						elif line.startswith("** "):
							amm.append("-")
							done=True
							break
					if not done:
						amm.append("-")
				if line.startswith("** AMH"):
					done=False
					for line in stdout:
						if line.startswith("c [appmc] Number of solutions is:"):
							amh.append(line.split(" ")[-1].strip())
							done=True
							break
						elif line.startswith("** "):
							amh.append("-")
							done=True
							break
					if not done:
						amh.append("-")
				if line.startswith("** ASH"):
					done=False
					for line in stdout:
						if line.startswith("c [appmc] Number of solutions is:"):
							ash.append(line.split(" ")[-1].strip())
							done=True
							break
						elif line.startswith("** "):
							ash.append("-")
							done=True
							break
					if not done:
						ash.append("-")
				if line.startswith("** ASM"):
					done=False
					for line in stdout:
						if line.startswith("c [appmc] Number of solutions is:"):
							asm.append(line.split(" ")[-1].strip())
							done=True
							break
						elif line.startswith("** "):
							asm.append("-")
							done=True
							break
					if not done:
						asm.append("-")
		with open(join(instance,"0"+str(run),"stderr.log"),"r") as stderr:
			for line in stderr:
				if line.startswith("** counterSharp"):
					done=False
					for line in stderr:
						if line.startswith("[runlim] space:"):
							counterM.append(line.split("\t")[-1].split(" ")[0].strip())
						elif line.startswith("[runlim] real:"):
							counterT.append(line.split("\t")[-1].split(" ")[0].strip())
						elif line.startswith("** "):
							break
				if line.startswith("** AMM"):
					done=False
					for line in stderr:
						if line.startswith("[runlim] space:"):
							ammM.append(line.split("\t")[-1].split(" ")[0].strip())
						elif line.startswith("[runlim] real:"):
							ammT.append(line.split("\t")[-1].split(" ")[0].strip())
						elif line.startswith("** "):
							break
				if line.startswith("** AMH"):
						done=False
						for line in stderr:
							if line.startswith("[runlim] space:"):
								amhM.append(line.split("\t")[-1].split(" ")[0].strip())
							elif line.startswith("[runlim] real:"):
								amhT.append(line.split("\t")[-1].split(" ")[0].strip())
							elif line.startswith("** "):
								break
				if line.startswith("** ASM"):
						done=False
						for line in stderr:
							if line.startswith("[runlim] space:"):
								asmM.append(line.split("\t")[-1].split(" ")[0].strip())
							elif line.startswith("[runlim] real:"):
								asmT.append(line.split("\t")[-1].split(" ")[0].strip())
							elif line.startswith("** "):
								break
				if line.startswith("** ASH"):
						done=False
						for line in stderr:
							if line.startswith("[runlim] space:"):
								ashM.append(line.split("\t")[-1].split(" ")[0].strip())
							elif line.startswith("[runlim] real:"):
								ashT.append(line.split("\t")[-1].split(" ")[0].strip())
							elif line.startswith("** "):
								break
	
	print(instance,end='')
	print(' ',end='')
	print(str(median(counterM))+" ",end='')
	print(str(median(counterT))+" ",end='')
	print(str(median(ammM))+" ",end='')
	print(str(median(ammT))+" ",end='')
	print(str(median(amhM))+" ",end='')
	print(str(median(amhT))+" ",end='')
	print(str(median(asmM))+" ",end='')
	print(str(median(asmT))+" ",end='')
	print(str(median(ashM))+" ",end='')
	print(str(median(ashT))+" ",end='')
	print(' | ',end='')
	print(' '.join(amm),end='')
	print(' | ',end='')
	print(' '.join(amh),end='')
	print(' | ',end='')
	print(' '.join(asm),end='')
	print(' | ',end='')
	print(' '.join(ash),end='')
	print()
	
