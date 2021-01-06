# DAFT PUNK HELMET
#  
# Have fun =)
#
# This file is part of the Estefannie Explains It All repo.
#
# (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code.

import sys
import pyaudio
from struct import unpack
import numpy as np
import serial
import time
import threading

spectrum  = [1,1,1,3,3,3,2,2]
matrix    = [0,0,0]
power     = []
weighting = [2,32,64] 
ser = serial.Serial('/dev/tty96B0', 9600)
running = True
def serial_thread():
    global matrix

    while running:
#        print ser.readline()
        time.sleep(0.07)
        levels = ""
        for each in matrix:
            levels += str(each) + ","

        levels = "s" + levels[:-1]

        print levels
        ser.write(levels) 

def list_devices():
    # List all audio input devices
    p = pyaudio.PyAudio()
    i = 0
    n = p.get_device_count()
    while i < n:
        dev = p.get_device_info_by_index(i)
        if dev['maxInputChannels'] > 0:
           print(str(i)+'. '+dev['name'])
        i += 1

# Audio setup
no_channels = 1
sample_rate = 44100

# Chunk must be a multiple of 8
# NOTE: If chunk size is too small the program will crash
# with error message: [Errno Input overflowed]
chunk = 3072 

list_devices()
# Use results from list_devices() to determine your microphone index
device = 0 

print device

p = pyaudio.PyAudio()
stream = p.open(format = pyaudio.paInt16,
                channels = no_channels,
                rate = sample_rate,
                input = True,
                frames_per_buffer = chunk,
                input_device_index = device)


# Return power array index corresponding to a particular frequency
def piff(val):
    return int(2*chunk*val/sample_rate)
   
def calculate_levels(data, chunk,sample_rate):
    global matrix
    # Convert raw data (ASCII string) to numpy array
    data = unpack("%dh"%(len(data)/2),data)
    data = np.array(data, dtype='h')
    # Apply FFT - real data
    fourier=np.fft.rfft(data)
    # Remove last element in array to make it the same size as chunk
    fourier=np.delete(fourier,len(fourier)-1)
    # Find average 'amplitude' for specific frequency ranges in Hz
    power = np.abs(fourier)   
    matrix[0]= int(np.mean(power[piff(0)    :piff(500):1]))
    matrix[1]= int(np.mean(power[piff(500)  :piff(2000):1]))
    matrix[2]= int(np.mean(power[piff(2000) :piff(20000):1]))
    
    matrix=np.divide(np.multiply(matrix,weighting),10000)

   # Set floor at 0 and ceiling at 8 for LED matrix
    matrix=matrix.clip(0,512)
    return matrix

# Main loop
t = threading.Thread(target=serial_thread)
t.start()

while 1:
    try:
        # Get microphone data
        data = stream.read(chunk)
        matrix=calculate_levels(data, chunk,sample_rate)

    except KeyboardInterrupt:
        print("Ctrl-C Terminating...")
        stream.stop_stream()
        stream.close()
        p.terminate()
        ser.close()
        running = False
        sys.exit(1)
    except Exception, e:
        print(e)
        print("ERROR Terminating...")
        stream.stop_stream()
        stream.close()
        p.terminate()
        ser.close()
        running = False
        sys.exit(1)
