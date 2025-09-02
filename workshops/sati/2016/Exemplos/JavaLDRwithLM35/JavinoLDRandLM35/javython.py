import sys
import serial
OP=sys.argv[1]
PORT=sys.argv[2]
MSG=sys.argv[3]
try:
	comm = serial.Serial(PORT, 9600)
	comm.open
	comm.isOpen
	if(OP=='command'):
		comm.write(MSG)
	if(OP=='request'):
		comm.write(MSG)
		print (comm.readline())
	if(OP=='listen'):
		print (comm.readline())
	comm.close
except:
	print ("Error on conect "+PORT)
	sys.exit(1)
