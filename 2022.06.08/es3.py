#start: 10:25

import os

def printTable(fl):
	with open(fl,"r") as openfl:
		myline = [];
		myline.append("-")
		myline.append("-")
		for line in openfl.read().splitlines():
			info = line.split()[0]
			if info == "Name:":
				myline[0] = line.split()[1]
			elif info == "VmSize:":
				myline[1] = line.split()[1]
		print("{:<20}{:<8}\tkB".format(myline[0],myline[1]));

if __name__ == "__main__":
	UID = os.getuid()
	
	allProc = [os.path.join("/proc", f) for f in os.listdir("/proc")]
	
	allStatus = []

	for f in allProc:
		if os.path.split(f)[1].isnumeric() and os.stat(f).st_uid == UID:
			allPath = os.path.join(f,"status")
			allStatus.append(allPath)
	
	print("name\t\t\tvmSize");
	
	for fl in allStatus:
		printTable(fl);
		
#11:00
