# BB-Cake
#  
# Have fun =)
#
# This file is part of the Estefannie Explains It All repo.
#
# (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code.


import RPi.GPIO as GPIO
import time
import os
import random

buttonPin = 16
music = None
ledPin = 3

GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(buttonPin, GPIO.IN)
GPIO.setup(ledPin, GPIO.OUT)

p = GPIO.PWM(12, 50)
p.start(10.5)

bb8_sounds = ['mpg321 /home/pi/Desktop/bb8/bb8_sounds/bb8_1.mp3', 'mpg321 /home/pi/Desktop/bb8/bb8_sounds/bb8_2.mp3']

def sound():
	randomSound = random.choice (bb8_sounds)
	music = os.popen(randomSound)

try:
	while True:
		buttonState = GPIO.input(buttonPin)
		if buttonState == 1:
			GPIO.output(ledPin, GPIO.HIGH)
			sound()
			GPIO.output(ledPin, GPIO.LOW)
			p.ChangeDutyCycle(10.5)  
			time.sleep(1) 
			p.ChangeDutyCycle(8.5)  
			time.sleep(1) 
			GPIO.output(ledPin, GPIO.HIGH)
			sound()
			GPIO.output(ledPin, GPIO.LOW)
			p.ChangeDutyCycle(10.5)
			time.sleep(1) 
			GPIO.output(ledPin, GPIO.HIGH)
			sound()
			GPIO.output(ledPin, GPIO.LOW)
			buttonState = 0
			print buttonState
except KeyboardInterrupt:
	p.stop()
        GPIO.cleanup()
