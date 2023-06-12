import os
import sys

def findAllptn(directory):
	
	for (dirpath,dirname,flname) in os.walk(directory):
		for fl in flname:
			if pattern in fl:
				flpath = os.path.join(dirpath,fl)
				allMatched.append(flpath)	
				

if __name__ == "__main__":
	pattern = sys.argv[1]

	allMatched = []

	findAllptn("./")

	print(*allMatched, sep = "\n")
	
	

