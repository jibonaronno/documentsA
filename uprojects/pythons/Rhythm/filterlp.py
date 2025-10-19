import numpy as np
from scipy.signal import butter,filtfilt

class LowpassFilter(object):
    def __init__(self):
        self.T = 10.0
        self.fs = 10.1
        self.cutoff = 2
        self.nyq = 0.5 * self.fs
        self.order = 2
        self.n = int(self.T * self.fs)
        self.data = []

    def butter_lowpass_filter(self, data, cutoff=2, fs=10, order=2):
        normal_cutoff = self.cutoff / (0.5 * fs)
        # Get the filter coefficients 
        b, a = butter(self.order, normal_cutoff, btype='low', analog=False)
        y = filtfilt(b, a, data)
        return y

    def genSampleData(self):
        # sin wave
        sig = np.sin(1.2*2*np.pi*self.T)
        # Lets add some noise
        noise = 1.5*np.cos(9*2*np.pi*self.T) + 0.5*np.sin(12.0*2*np.pi*self.T)
        self.data = sig + noise
        return self.data
        
        '''
        # Filter the data, and plot both the original and filtered signals.
        y = self.butter_lowpass_filter(self.data, self.cutoff, self.fs, self.order)
        fig = go.Figure()
        fig.add_trace(go.Scatter(
                    y = self.data,
                    line =  dict(shape =  'spline' ),
                    name = 'signal with noise'
                    ))
        fig.add_trace(go.Scatter(
                    y = y,
                    line =  dict(shape =  'spline' ),
                    name = 'filtered signal'
                    ))
        fig.show()
        '''

