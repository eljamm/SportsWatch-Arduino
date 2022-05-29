from scipy.interpolate import make_interp_spline
import scipy.signal as signal
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

a = []
b = []
max=500		# Number of lines to process

with open('data.csv', 'r') as data:
    lines = pd.read_csv(data, nrows=max, header=None)	# Get lines from csv file
    for index in range(max):
        row = lines.iloc[index].values	# Read the row's Array
        ECG = float(row[3])
        a.append(index)
        b.append(ECG)
    
    # Create numpy arrays for processing
    x = np.array(a)
    y = np.array(b)
    
    # Interpolation (Smoothing)
    spline = make_interp_spline(x, y)
    X_ = np.linspace(x.min(), x.max(), 2000)
    Y_ = spline(X_)
    
    # Low-Pass Buterworth filter
    N  = 2    # Filter order
    Wn = 0.06 # Cutoff frequency
    B, A = signal.butter(N, Wn, output='ba')
    Y_F = signal.filtfilt(B,A, Y_)
    
    # Plotting
    plt.plot(X_, Y_F)
    plt.title("Processed ECG Signal")
    plt.xlabel("Milliseconds (ms)")
    plt.ylabel("ECG")
    plt.show()
