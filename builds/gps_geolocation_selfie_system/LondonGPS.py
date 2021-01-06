#Import all necessary libraries
import time
import gpsd
import math
from goprocam import GoProCamera
from goprocam import constants

#Need this to calculate the where I am 
earthRadius = 6371

#Wait for the Pi to boot and get the GoPro Wifi
time.sleep(20)

#Connect to the local gpsd
gpsd.connect()

#Initialize the camera object
camera = GoProCamera.GoPro()

#Saved Locations for this trip: 
#Platform 9 3/4: 51.5322° , -0.1240°
#Abbey Road: 51.5321° , -0.1781°
#Buckingham 51.5014°, -0.1419°
#Big Ben 51.5007° , -0.1246°
#Tower of London 51.5081° , -0.0759°
#Tower Bridge 51.5055° , -0.0754° 
#Shakespeare Globe 51.5081° , -0.0972°
#Sweetings 51.5125° , -0.0928°

#Create location arrays: 
latitude = [51.5110, 51.5322, 51.5321, 51.5014, 51.5007, 51.5081, 51.5055, 51.5081, 51.5125]
longitude = [-0.1863, -0.1240, -0.1781, -0.1419, -0.1246, -0.0759, -0.0754, -0.0972, -0.0928]

# Main loop to check the coordinates that I am at 
# and the coordinates I’ve saved.
while True:
       received = False
       try:
               packet = gpsd.get_current()
               received = True
       except Exception:
               print("No signal")
       if received == True:
               #get my current position
               currentPost = packet.position()
               currentLat = currentPost[0]
               currentLon = currentPost[1]
               for location in range(len(latitude)):
                 
                       # The angles need to be in radians to pass 
                       # to trig functions
                       dLat = math.radians(latitude[location] - currentLat)
                       dLon = math.radians(longitude[location] - currentLon)
                       
                       # I used the ‘haversine’ formula to calculate 
                       # the distance between two points over the 
                       # earth’s surface. 
                       # a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
                       # c = 2 ⋅ atan2( √a, √(1−a) )
                       #d = R ⋅ c
                       a = math.sin(dLat/2) * math.sin(dLat/2) + math.cos(math.radians(latitude[location])) * math.cos(math.radians(currentLat)) * math.sin(dLon/2) * math.sin(dLon/2)
                       c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
                       d = earthRadius * c
                       
                       # d is distance between the two sets of coordinates
                       # if distance is less than 10m unit of d is in km, 
                       # take a picture
                       if d < 0.01:
                       camera.take_photo(0)
       
       #we need to sleep so it doesn't infinitely poll
       time.sleep(1)
