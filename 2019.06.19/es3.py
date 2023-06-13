import os
import sys


def countln(filepath):
	count = 0
	for flp in filepath:
		with open(flp,"r") as fl:
			fllen = len(fl.readlines())
			count += fllen
			print("{:<100}{}".format(flp,fllen))	
	print()
	return count

if __name__ == "__main__":
	directory = sys.argv[1]
	allC = []
	allH = []
	allMK = []
	sumln = 0
	
	for dirpath, dirname, filename in os.walk(directory):
		for fl in filename:
			path = os.path.join(dirpath,fl);
			if fl.endswith(".c"):
				allC.append(path);
			elif fl.endswith(".h"):
				allH.append(path)
			elif fl == "Makefile":
				allMK.append(path)

	if (allC):
		sumln += countln(allC)
	if (allH):
		sumln += countln(allH)
	if (allMK):
		sumln += countln(allMK)
		
	print("{:<100}{}".format("tot source", sumln))
