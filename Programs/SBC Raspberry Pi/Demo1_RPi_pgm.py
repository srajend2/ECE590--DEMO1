#Demo 1 Program

import serial
import time
import string
DEVICE = '/dev/ttyACM15'
BAUD = 9600
ser= serial.Serial(DEVICE, BAUD)
#initializing Data to low values, in this case 2 is considered low
#and 1 is considered high
Data = 222
preval1 = '0'
preval2 = '0'
preval3 = '0'
#to make sure any bad chunk of data is ignored during the initial reception
for cnt1 in range(0,20):
	Data=ser.readline()
	print "Printed:", cnt1

while (1):
        Data=ser.readline()
        print "-------------"
        print "received data", Data
        s1=Data[0]
        s2=Data[1]
        s3=Data[2]
        print 'S1=',s1
        print 'S2=',s2
        print 'S3=',s3
	if ((preval1 != s1) | (preval2 != s2) | (preval3 != s3)) :
	     valchg = 'Y'
	     preval1 = s1
	     preval2 = s2
	     preval3 = s3
	else:
	     valchg = 'N'
     	if valchg == 'Y' :
           if s3!='2' :
             if s1=='2' :
                if s2=='2'  :
                    ser.write('0350 0000')
                    print 'right'
                elif s2=='1' :
                    ser.write('0000 1524')
                    print 'left'
             elif s1=='1' :
                    ser.write('1374 0350')
                    print 'reverse'
                    time.sleep(2)
		    ser.write('0000 1524')
		    print 'left'
           else :
                print 'go straight for sometime - cross the line'
                ser.write('0350 1374')
                print 'forward'
                time.sleep(3)
#               while(1):
                ser.write('0000 0000')
                print 'stop'
                exit()


