from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

"""
Generate square wave signal with the following parameters
Parameters:
f : frequency of square wave in Hertz overSampRate : oversampling rate (integer)
nCyl : number of cycles of square wave to generate

"""
f = 10 # f = 10Hz
overSampRate = 30 # oversampling rate
nCyl = 1 # number of cycles to generate
fs = overSampRate * f # sampling frequency

# time base
t = np.arange(start = 0, 
              stop = nCyl * 1 / f - 1 / fs, 
              step = 1 / fs) 

g = np.sign(np.sin(2*np.pi*f*t)) # replace with cos if a cosine wave is desired
g = signal.square(2 * np.pi * f * t, duty = 0.5)

# normalize for 12bit DAC resolution
g = (4096*(g - np.min(g))/np.ptp(g)).astype(int)  

plt.plot(t,g); 
plt.show()