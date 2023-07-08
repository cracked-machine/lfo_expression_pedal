from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

f = 10 # f = 10Hz
overSampRate = 30 # oversampling rate
nCyl = 1 # number of cycles to generate
fs = overSampRate * f # sampling frequency

# time base
t = np.arange(start = 0, 
              stop = (nCyl * 1 / f - 1 / fs), 
              step = 1 / fs) 

# t = np.linspace(0, 1, 500)
triangle = signal.sawtooth(2 * np.pi * f * t, 0.5)
plt.plot(t, triangle)
plt.show()