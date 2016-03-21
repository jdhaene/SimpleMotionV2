#!/usr/bin/python
from time import sleep
import simplemotion
handle = simplemotion.openBus('/dev/ttyUSB0')
devs = [1,2,3,5,6,7]
for i in range(3):
	faults = []
	for dev in devs:
		status = simplemotion.getParameter(handle,dev,552)
		print "Dev %d status %d"%(dev,status)
		if status != 0:
			faults.append(dev)
	if len(faults) == 0:
		print "Status OK"
		break
	print "Clear faults for devices ",faults
	for dev in faults:
		simplemotion.setParameter(handle,dev,552,0)
	sleep(3)
