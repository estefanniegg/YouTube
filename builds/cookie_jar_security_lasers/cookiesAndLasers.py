# Cookie Jar Laser Surveillance Security System 
#  
# Have fun =)
#
# This file is part of the Estefannie Explains It All repo.
#
# (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code.

from gpiozero import LightSensor, Buzzer
from time import sleep
from twython import Twython
from picamera import PiCamera
from time import sleep
from datetime import datetime
import random

camera = PiCamera()

ldr = LightSensor(4)
ldr2 = LightSensor(19)
ldr3 = LightSensor(15)
ldr4 = LightSensor(18)
ldr5 = LightSensor(26)
ldr6 = LightSensor(22)
ldr7 = LightSensor(23)
ldr8 = LightSensor(24)
ldr9 = LightSensor(25)
ldr10 = LightSensor(27)

buzzer = Buzzer(17)

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

messages = [
        "Caught the cookie thief!",
        "Ahhhh!",
        "BUSTED!",
        "Intruder"
]

while True:
        if ldr.value > 0.01 and ldr2.value > 0.01 and ldr3.value > 0.01 and ldr4.value > 0.01 and ldr5.value > \ 
        0.01 and ldr6.value > 0.01 and ldr7.value > 0.01 and ldr8.value > 0.01 and ldr9.value > 0.01 and ldr10.value > 0.01 and :
                buzzer.off()
                print "Safe"
        else:
                message = random.choice(messages)
                timestamp = datetime.now().isoformat()
                photo_path = '/home/pi/Desktop/cookiepics/%s.jpg' % timestamp
                camera.capture(photo_path)
                with open(photo_path, 'rb') as photo:
                twitter.update_status_with_media(status=message, media=photo)
                buzzer.on()
                print "Intruder!"


