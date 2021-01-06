import RPi.GPIO as GPIO
import time
import sys
import httplib, urllib
from hx711 import HX711

def cleanAndExit():
    print "Cleaning..."
    GPIO.cleanup()
    print "Bye!"
    sys.exit()

hx = HX711(5,6)

hx.set_reading_format("LSB", "MSB")

hx.set_reference_unit(113)

hx.reset()
hx.tare()
prevWeight = hx.get_weight(5)
threshold = 5
while True:
    try:
        val = hx.get_weight(5)
        print val

        if (val < (prevWeight - threshold)):
            print "Weight has changed!"
            conn = httplib.HTTPSConnection("api.pushover.net:443")
            conn.request("POST", "/1/messages.json",
                    urllib.urlencode({
                        "token": "*******",
                        "user": "*******",
                        "message": "Santa is here",
                        }), { "Content-type": "application/x-www-form-urlencoded" })
            time.sleep(0.5)
            conn.getresponse()
        hx.power_down()
        hx.power_up()
        prevWeight = val
        time.sleep(1)
    except (KeyboardInterrupt, SystemExit):
        cleanAndExit()
