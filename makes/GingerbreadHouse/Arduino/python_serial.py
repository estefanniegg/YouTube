# SMART GINGERBREAD HOUSE
#  
# Have fun =)
#
# This file is part of the Estefannie Explains It All repo.
#
# (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code.
#

import serial
import time
import urllib2

serial1 = serial.Serial('/dev/ttyACM0', 9600)

lightState = 0
musicState = 0
doorState = 0
gingerState = 0
houseState = 0
everythingState = 0

while True:
	christmasLights = urllib2.urlopen("http://localhost/LEDstate.txt").read();
	music = urllib2.urlopen("http://localhost/soundState.txt").read();
	frontDoor = urllib2.urlopen("http://localhost/doorState.txt").read();
	gingerbreadMen = urllib2.urlopen("http://localhost/gingerbreadMenState.txt").read();
	houseLights = urllib2.urlopen("http://localhost/indoorLedState.txt").read();
	everything = urllib2.urlopen("http://localhost/allStates.txt").read();

	if int(christmasLights) == 1 and lightState == 0:
		print("ON")
		lightState = 1
		serial1.write('C')
	elif int(christmasLights) == 0 and lightState == 1:
		print("OFF")
		lightState = 0
		serial1.write('O')
	if int(music) == 1 and musicState == 0:
		print("ON")
		musicState = 1
		serial1.write('J')
	elif int(music) == 0 and musicState == 1:
		print("OFF")
		musicState = 0
		serial1.write('B')
	if int(frontDoor) == 1 and doorState == 0:
		print("OPEN")
		doorState = 1
		serial1.write('D')
	elif int(frontDoor) == 0 and doorState == 1:
		print("CLOSED")
		doorState = 0
		serial1.write('F')
	if int(gingerbreadMen) == 1 and gingerState == 0:
		print("DANCE")
		gingerState = 1
		serial1.write('M')
	elif int(gingerbreadMen) == 0 and gingerState == 1:
		print("STOP")
		gingerState = 0
		serial1.write('G')
	if int(houseLights) == 1 and houseState == 0:
		print("ON")
		houseState = 1
		serial1.write('I')
	elif int(houseLights) == 0 and houseState == 1:
		print("OFF")
		houseState = 0
		serial1.write('P')
	if int(everything) == 1 and everythingState == 0:
		print("ON")
		everythingState = 1
		serial1.write('E')
	elif int(houseLights) == 0 and houseState == 1:
		print("OFF")
		houseState = 0
		serial1.write('N')
	#time.sleep(1)
