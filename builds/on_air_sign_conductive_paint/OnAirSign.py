import RPi.GPIO as GPIO
import time
from twython import Twython
import signal, sys, MPR121
import datetime

now = datetime.datetime.now()

sensor = MPR121.begin()
touch_threshold = 40
release_threshold = 20
sensor.set_touch_threshold(touch_threshold)
sensor.set_release_threshold(release_threshold)

from auth import (
    consumer_key,
    consumer_secret,
    access_token,
    access_token_secret
)

twitter = Twython(
    consumer_key,
    consumer_secret,
    access_token,
    access_token_secret
)

#GPIO pin numbers
red = 12
green = 13
blue = 15

GPIO.setmode(GPIO.BOARD)
GPIO.setup(red, GPIO.OUT)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)

def turnColor(R,G,B):
	if R == True:
		GPIO.output(red, GPIO.HIGH)
	else: 
        GPIO.output(red, GPIO.LOW)
	if G == True:
	    GPIO.output(green, GPIO.HIGH)
	else: 
	    GPIO.output(green, GPIO.LOW)
	if B == True:
	    GPIO.output(blue, GPIO.HIGH)
	else:
	    GPIO.output(blue, GPIO.LOW)

while True:
	if sensor.touch_status_changed():
		sensor.update_touch_data()
		#Loop trough the PiCap's pins
		for i in range(12):
			if sensor.is_new_touch(i):
				if i == 1:
					#Neutral State: White LEDs
					turnColor(True,True,True)	
				elif i == 3:
					#Started Filming State: Blue LEDs
					turnColor(False,False,True)	
					message = "I started filming a new video! Woooooo! #newvideosoon" + now.strftime("%H:%M:%S")
					twitter.update_status(status=message)
					print("Tweeted: %s" % message)
				elif i == 5:
					#Stuck State: Red LEDs
					turnColor(True,False, False)
					message = "I am stuck. Prototype down. Still filming though.. #debugging #newvideosoon" + now.strftime("%H:%M:%S")
					twitter.update_status(status=message)
					print("Tweeted: %s" % message)
				elif i == 7:
					#Eating State: Purple LEDs
					turnColor(True,True,False)
					message = "Pizza time #filmingfood"
					twitter.update_status(status=message)
					print("Tweeted: %s" % message)
				elif i == 9:
					#Done Filming State: Green LEDs
					turnColor(False,True, False)
					message = "I am done filming. Woooooo! #editingtime #newvideosoon" + now.strftime("%H:%M:%S")
					twitter.update_status(status=message)
					print("Tweeted: %s" % message)
				else:
					#Neutral State: White LEDs  
					turnColor(True, True, True)
