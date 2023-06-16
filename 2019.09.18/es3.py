import os
import sys

if __name__ == "__main__":
	mydict = {}
	directory = sys.argv[1]
	for dirpath, dirname, filename in os.walk(directory):
		for fl in filename:
			fullPath = os.path.join(dirpath,fl)
			ino = os.stat(fullPath).st_ino
			if ino not in mydict.keys():
				mydict[ino] = [fullPath]
			else:
				mydict.get(ino).append(fullPath)
				
	for key in mydict.keys():
		allPath = mydict.get(key)
		if len(allPath) > 1:
			print(*allPath)
			
