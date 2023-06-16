import sys
import os

ELFMAGIC = [0x7f,0x45,0x4c,0x46]
enc = 'cp437'

def countBytesELF(directory):
	filesDir = []
	sumBytes= 0
	
	for files in os.listdir(directory):
		path = os.path.join(directory,files)
		if os.path.isfile(path):
			filesDir.append(files)
		elif os.path.isdir(path):
			sumBytes += countBytesELF(path)
			
	
	for fl in filesDir:
		path = os.path.join(directory,fl)
		with open(path,"r", encoding = enc) as openfl:
			file_head = openfl.read(4)
			if(file_head.startswith(ELFMAGIC)):
				sumBytes += os.stat(path).st_size
	
	return sumBytes
		
	

if __name__ == "__main__":
	
	if (len(sys.argv) == 1):
		print("Bytes of ELF files in .: 	{}\n".format(countBytesELF(".")))
	else:
		totalBytes = 0
		for directory in sys.argv[1:]:
			totalBytes += countBytes(directory)
	
		print(totalBytes)
	
	

