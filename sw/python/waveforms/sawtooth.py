

import numpy as np
from scipy import signal
import matplotlib.pyplot as plt

f = 10 # f = 10Hz
overSampRate = 30 # oversampling rate
nCyl = 1 # number of cycles to generate
fs = overSampRate * f # sampling frequency

# time base
t = np.arange(start = 0, 
              stop = (nCyl * 1 / f - 1 / fs), 
              step = 1 / fs) 

g = signal.sawtooth(2 * np.pi * f * t)

# normalize for 12bit DAC resolution
g = (4096*(g - np.min(g))/np.ptp(g)).astype(int)  

plt.plot(t, g)
plt.title('Sawtooth Wave f=' + str(f) + ' Hz') # plot title
plt.xlabel('Time (s)') # x-axis label
plt.ylabel('Amplitude') # y-axis label
plt.show() # display the figure