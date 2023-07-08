import numpy as np
import matplotlib.pyplot as plt # library for plotting

"""
Generate sine wave signal with the following parameters
Parameters:
f : frequency of sine wave in Hertz 
overSampRate : oversampling rate (integer)
phase : desired phase shift in radians
nCyl : number of cycles of sine wave to generate
"""

f = 10 #frequency = 10 Hz
overSampRate = 17 #oversammpling rate
phase = 1/3*np.pi #phase shift in radians
nCyl = 1 # desired number of cycles of the sine wave

fs = overSampRate * f # sampling frequency

# time base
t = np.arange(start = 0, 
              stop = nCyl * 1 / f - 1 / fs, 
              step = 1 / fs) 

g = np.sin(2 * np.pi * f * t + phase) # replace with cos if a cosine wave is desired

# normalize for 12bit DAC resolution
g = (511*(g - np.min(g))/np.ptp(g)).astype(int)  

g2 = ','.join([str(i) for i in g])
print(len(g))
print(g2)

plt.plot(t, g) # plot using pyplot library from matplotlib package
plt.title('Sine wave f=' + str(f) + ' Hz') # plot title
plt.xlabel('Time (s)') # x-axis label
plt.ylabel('Amplitude') # y-axis label
plt.show() # display the figure