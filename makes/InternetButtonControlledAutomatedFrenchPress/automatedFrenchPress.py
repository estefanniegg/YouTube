/* INTERNET BUTTON CONTROLLED AUTOMATED FRENCH PRESS
 *  
 * Have fun =)
 *
 * This file is part of the Estefannie Explains It All repo.
 *
 * (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

from urllib2 import Request, urlopen, URLError #import libraries
import unirest #import unirest
import json #import json library

import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306
import Image
import ImageDraw
import ImageFont

import RPi.GPIO as GPIO
import time


#-------------------------------------------------------RASPBERRY PI CONFIG-------------------------------------------------------------------------------------
#OLED
RST = 24
DC = 23
SPI_PORT = 0
SPI_DEVICE = 0

# STEPPER MOTORS
motorStep1 = 27
motorDirection1 = 22

motorStep2 = 5
motorDirection2 = 6

# CALIBRATION BUTTON
buttonPin = 16

GPIO.setmode(GPIO.BCM)
GPIO.setup(motorStep1, GPIO.OUT)
GPIO.setup(motorDirection1, GPIO.OUT)
GPIO.setup(motorStep2, GPIO.OUT)
GPIO.setup(motorDirection2, GPIO.OUT)
GPIO.setup(buttonPin, GPIO.IN)

#-------------------------------------------------------OLED STUFF-------------------------------------------------------------------------------------

disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST, dc=DC, spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE, max_speed_hz=8000000))
disp.begin()
disp.clear()
disp.display()

#DISPLAY CONFIG
width = disp.width
height = disp.height
padding = 1
top = padding
x = padding # Move left to right keeping track of the current x position for drawing shapes.
font = ImageFont.truetype('clockFont.ttf', 56)
smallFont = ImageFont.truetype('clockFont.ttf', 24)

#START - for timer
start = time.time()

#IMAGE - for completion
happyCat = Image.open('happycat_coffee_64.ppm').convert('1')    

def displayCalibrationMsg():
        textImage = Image.new('1', (width,height))
        draw = ImageDraw.Draw(textImage)    
        draw.text((x, top), 'Hello World!', font=smallFont, fill=255)
        draw.text((x, top + 25), 'Calibrating...', font=smallFont, fill=255)

        disp.image(textImage)
        disp.display()

def displayReadyToBrew():
        textImage = Image.new('1', (width,height))
        draw = ImageDraw.Draw(textImage)    
        draw.text((x, top), 'Ready', font=smallFont, fill=255)
        draw.text((x, top + 25), 'to brew.', font=smallFont, fill=255)
        disp.image(textImage)
        disp.display()

def displayTimer():
        currentTime = time.time() - start
        h, rem = divmod(currentTime, 3600)
        m, s = divmod(rem, 60)
        textImage = Image.new('1', (width,height))
        draw = ImageDraw.Draw(textImage)    
        draw.rectangle((0,0,width,height), outline=0, fill=0)
        draw.text((x, top),"{:0>2}:{:02.0f}".format(int(m), s), font=font, fill=255)
        disp.image(textImage)
        disp.display()

def displayPressing():
        textImage = Image.new('1', (width,height))
        draw = ImageDraw.Draw(textImage)    
        draw.text((x, top), 'Pressing...', font=smallFont, fill=255)
        disp.image(textImage)
        disp.display()

def displayHappyCat():
        disp.image(happyCat)
        disp.display()

def wipeScreen():
        disp.clear()
        disp.display()

#-------------------------------------------------------PRESS STUFF-------------------------------------------------------------------------------------

currentState = 0; # ACTIVITIES
stepCounter = 0; # TO CALIBRATE
stepsToTop = 3000; # STEPS TO TRAVEL
stepTime = 0.001 # ROTATION SPEED
coffeeWaitTime = 393 # BREWING TIME
coffeeTime = 0 #TRACKER

#-------------------------------------------------------INTERNET BUTTON STUFF-------------------------------------------------------------------------------------
def internetButtonListener():
        try:
                response = unirest.get("https://api.particle.io/v1/devices/[your key]/buttonPress?access_token=[your token]", #try unirest API call
                        headers=
                        {
                        "accesstoken": "[your token]", #access key
                        "Content-Type": "application/x-www-form-urlencoded", #content type
                        "accept": "application/json" #verify JSON
                        },
                        params={ "parameter": 23, "foo": "bar"} #give parameters
                        )
                acceleration = response.raw_body #create variable to hold JSON response
                json_string = acceleration #use json, turn it into dictionary
                parsed_json = json.loads(acceleration) #parsed_json is now dictionary for response
            
                x_accelParse = (parsed_json["result"]) #print parsed json
                print x_accelParse

                return (x_accelParse)
    
        except URLError, e:
                print 'could not contact photon', e #throw URL error if API can't be contacted
    
def greenButton():
        unirest.post("https://api.particle.io/v1/devices/[your key]/green?access_token=[your token]", headers={ "accesstoken": "[your token]", "Accept": "application/json" }, params={ "parameter": 23, "foo": "bar" })

def clearButton():
        unirest.post("https://api.particle.io/v1/devices/[your key]/none?access_token=[your token]", headers={ "accesstoken": "[your token]", "Accept": "application/json" }, params={ "parameter": 23, "foo": "bar" })

def rainbowButton():
        unirest.post("https://api.particle.io/v1/devices/[your key]/song?access_token=[your token]", headers={ "accesstoken": "[yourtoken]", "Accept": "application/json" }, params={ "parameter": 23, "foo": "bar" })

def blueButton():
        unirest.post("https://api.particle.io/v1/devices/[your key]/blue?access_token=[your token]", headers={ "accesstoken": "[your token]", "Accept": "application/json" }, params={ "parameter": 23, "foo": "bar" })

#-------------------------------------------------------ACTIVITY LOOP-------------------------------------------------------------------------------------

# CURRENTSTATE: 
# calibrate = 0 
# gototop = 1
# waitforpress = 2
# dothetime = 3
# pressthepress = 4

displayCalibrationMsg()

while True:
        buttonState = GPIO.input(buttonPin)
        # CURRENTSTATE: 0 (calibrate)
        # The motor steps in one direction until the calibration button on the 
        # base is pressed (true) and changes state to 1 (gototop)
        if currentState == 0:
                if buttonState == 0:
                        GPIO.output(motorDirection1, GPIO.HIGH)
                        GPIO.output(motorDirection2, GPIO.LOW)
                        time.sleep(stepTime)
                        GPIO.output(motorStep1, GPIO.LOW)
                        GPIO.output(motorStep2, GPIO.LOW)
                        time.sleep(stepTime)
                        GPIO.output(motorStep1, GPIO.HIGH)
                        GPIO.output(motorStep2, GPIO.HIGH)
                else:
                        print "New State: gototop"
                        currentState = 1
        # CURRENTSTATE: 1 (gototop)
        # The motor steps in the opposite direction until it the number of steps to the top 
        # equal to the steps counter. Set the current state to 2 (waitforpress)
        elif currentState == 1:
                if stepCounter == stepsToTop:
                        print "New State: waitforpress"
                        currentState = 2
                        greenButton()
                        wipeScreen()
                        displayReadyToBrew()
                else:
                        GPIO.output(motorDirection1, GPIO.LOW)
                        GPIO.output(motorDirection2, GPIO.HIGH)
                        time.sleep(stepTime)
                        GPIO.output(motorStep1, GPIO.LOW)
                        GPIO.output(motorStep2, GPIO.LOW)
                        time.sleep(stepTime)
                        GPIO.output(motorStep1, GPIO.HIGH)
                        GPIO.output(motorStep2, GPIO.HIGH)
                        stepCounter += 1
        # CURRENTSTATE: 2 (waitforpress)
        # We call listener and wait for the internet button's input. If true, we start the 
        # brewing timer and change the state to 3 (do the time)
        elif currentState == 2:
                internetButton = internetButtonListener()
                if internetButton != 0:
			print "New State: dothetime"
                        start = time.time()
                        coffeeTime = 0
			currentState = 3
        # CURRENTSTATE: 3 (dothetime)
        # Check the timer and if it hits the desired brewing time, change the state to 4 (pressthepress)
        elif currentState == 3:
		if coffeeTime == coffeeWaitTime:
                        wipeScreen()
                        blueButton()
                        displayPressing()
                        print "New State: pressthepress"
                        currentState = 4
                else:
                        wipeScreen()
                        displayTimer()
                        coffeeTime += 1
                        time.sleep(1)
        # CURRENTSTATE: 4 (pressthepress)
        # Step the motor down until the stepcounter is 0 and change the state to 1 (go to top)
        elif currentState == 4:
                if stepCounter == 0:
                        displayHappyCat()
                        rainbowButton()
                        print "New State: gototop"
                        currentState = 1
                        blueButton()
                else:
                        GPIO.output(motorDirection1, GPIO.HIGH)
                        GPIO.output(motorDirection2, GPIO.LOW)
                        time.sleep(.001)
                        GPIO.output(motorStep1, GPIO.LOW)
                        GPIO.output(motorStep2, GPIO.LOW)
                        time.sleep(.001)
                        GPIO.output(motorStep1, GPIO.HIGH)
                        GPIO.output(motorStep2, GPIO.HIGH)
                        stepCounter -= 1


