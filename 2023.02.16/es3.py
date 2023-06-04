import sys
import os

if __name__ == "__main__":
	if (len(sys.argv) != 2):
		sys.stderr.write('Invalid Arguments\n')
		exit()
	
	directory = sys.argv[1]
	
	filesDir = []
	
	#prendo solamente i file, le directory non mi interessano
	
	for path in os.listdir(directory):
		if os.path.isfile(os.path.join(directory,path)):
			filesDir.append(path)
			
	#ai fini dell'esercizio inutile in quanto directory contiene solo file di testo
	
	sumRow = []
	print(filesDir[:])
	
	for fl in filesDir:
		idxRow = 0		# 0 -> prima riga, 1 -> seconda riga ...
		with open(os.path.join(directory,fl),'r') as cfl:
			for row in cfl:
				try:
					sumRow[idxRow] += len(row) 
				except IndexError:
					sumRow.append(len(row))
				idxRow += 1
	
	for i in range(len(sumRow)):
		print("{}	{}".format((i+1),sumRow[i]))
	
	exit()
