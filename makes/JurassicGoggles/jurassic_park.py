# JURASSIC PARK GOGGLES
# 
# To find out how to do the Twitter authorization tokens
# go to projects.raspberrypi.org/en/projects/tweeting-babbage
#
# If you make these, please share them with me!
# 
# This file is part of the Estefannie Explains It All repo.
# 
# (c) Estefannie Explains It All
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code
 
from picamera import PiCamera
from datetime import datetime
from  random import choice
from time import sleep
from rpi_ws281x import *
import tweepy 
import json
import RPi.GPIO as GPIO
import time

#pixel
LED_COUNT = 14
LED_PIN = 12
LED_FREQ_HZ = 800000
LED_DMA = 10
LED_BRIGHTNESS = 255
LED_INVERT = False
LED_CHANNEL = 0
LED_STRIP = ws.SK6812_STRIP


#buttton object
buttonpin = 10
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(buttonpin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) 

#Red LED object
redLED = 8
GPIO.setup(redLED, GPIO.OUT, initial=GPIO.LOW)

print('GPIO setup done')
#Twitter authentication stuff
#opening the file with tokens
auth_file = open('twitter_auth.json', 'r')

print('twitter auth open')

secrets = json.load(auth_file)
auth = tweepy.OAuthHandler(secrets['consumer_key'], secrets['consumer_secret'])
auth.set_access_token(secrets['access_token'], secrets['access_token_secret'])
twitter = tweepy.API(auth)
auth_file.close()

print('twitter auth done')
#camera objact
camera = PiCamera()

twitter_file = open('twitterid.txt', 'r')
fileData = twitter_file.readline()
lastSearch = int(fileData)

print('file open')

#list of messages
dinosaurs = [
        "Tyrannosaurus detected...", 
        "Velociraptor detected...",
        "Diplodocus detected...",
        "Brachiosaurus detected...",
        "Albertosaurus detected...",
        "Triceratops detected...",
        "Stegosaurus detected...",
        "Brontosaurus detected..."
        ]

def progressLight(strip, index):
    strip.setPixelColor(index, Color(0, 150, 0))
    strip.show()

def take_photo():
    global photo_path
    timestamp = datetime.now().isoformat()
    photo_path = '/home/pi/Desktop/jurassic/%s.jpg' % timestamp
    camera.capture(photo_path)
    print("Done taking a picture")

def tweet(username):
    twitter.update_with_media(photo_path,  choice(dinosaurs) + '@' + username)
    print("Done tweeting")

def go(username, strip):
    clearLights(strip)
    colorWipe(strip, Color(150, 150, 150))
    take_photo()
    clearLights(strip)
    sleep(1)
    colorWipe(strip, Color(0, 0, 150))
    tweet(username)
    sleep(1)
    clearLights(strip)

def searchMentions(strip):
    global lastSearch
    for tweet in twitter.mentions_timeline(lastSearch):
        print(tweet.id, tweet.created_at, tweet.text, tweet.user.screen_name)
        print('Mention found')
        go(tweet.user.screen_name, strip)
        if (tweet.id > lastSearch):
            lastSearch = tweet.id

def emergencyCapture(strip):
    go('estefanniegg', strip)

timer = time.time()

jurassicTimer = time.time()
spinIndex = 0
def jurassicSpin(strip):
    global spinIndex
    global jurassicTimer
    if time.time() - jurassicTimer > 0.5:
        clearLights(strip)
        spinIndex = spinIndex + 1
        if spinIndex > 2:
            spinIndex = 0
        jurassicTimer = time.time()
    progressLight(strip, spinIndex)
    progressLight(strip, spinIndex + 3)
    progressLight(strip, spinIndex + 7)
    progressLight(strip, spinIndex + 10)


def wheel(pos):
    if pos < 85:
        return Color(pos * 3, 255 - pos * 3, 0)
    elif pos < 170:
        pos -= 85
        return Color(255 - pos * 3, 0, pos * 3)
    else: 
        pos -= 170
    return Color(0, pos * 3, 255 - pos * 3)

def colorWipe(strip, color, wait_ms=50):
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, color)
        strip.show()

def rotate(strip, color):
    for i in range(strip.numPixels()):
        for j in range(strip.numPixels()):
            strip.setPixelColor(j, color)
            strip.show()
            strip.setPixelColor(i, 0)
            strip.show()

def clearLights(strip):
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, 0)
    strip.show()

print('declarations done')

strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL, LED_STRIP)
strip.begin()
spinTimer = time.time()
pressedTimer = time.time()
activated = False
previousPressed = False
pressed = False
emergencyPicture = False
print('variables set')
try:
    #strip
    GPIO.output(redLED, GPIO.HIGH)
    while True:
        if activated:
            jurassicSpin(strip)
            if (time.time() - timer) > 5:
                searchMentions(strip)
                timer = time.time()
        else:
            clearLights(strip)
        if GPIO.input(10) == GPIO.HIGH:
            pressed = True
        elif GPIO.input(10) == GPIO.LOW:
            pressed = False
        if (pressed == True and previousPressed == False):
            pressedTimer = time.time()
        if (not emergencyPicture and pressed and (time.time() - pressedTimer) > 2):
            emergencyPicture = True
            print('take emergency picture')
            emergencyCapture(strip)
        if (pressed == False and previousPressed == True):
            if not emergencyPicture:
                activated = not activated
                print('button pressed')
            emergencyPicture = False
        previousPressed = pressed

except KeyboardInterrupt:
    GPIO.cleanup()

clearLights(strip)
camera.close()
twitter_file.close()
twitter_file = open('twitterid.txt', 'w')
twitter_file.write(str(lastSearch))
twitter_file.close()
