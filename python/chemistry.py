import numpy as np
from matplotlib import cm
import matplotlib.pyplot as plt
import logbin as lb
import glob
from scipy.optimize import fsolve
from scipy.interpolate import interp1d
from scipy.signal import savgol_filter
from scipy.interpolate import splev
from scipy.interpolate import splrep
import colorsys
import networkx as nx
import random
import math
import matplotlib.style
import matplotlib as mpl

def show_mixed():
    plt.figure()
    d_vec = [1, 2, 3]
    color_list = ['r', 'b', 'g']
    i = 0
    for d in d_vec:
        j = 0
        path = "/home/bnaya/Desktop/chimestry/results/mixed/d" + str(d) + "/*"
        for f in glob.glob(path):
            data = np.loadtxt(f)
            x, y = zip(*data)
            if j == 0:
                plt.loglog(x, y, '-o', color=color_list[i], label = r'$d = $' + str(d))
            else:
                plt.loglog(x, y, '-o', color=color_list[i])

            if j == 2:
                break
            j = j + 1
        i = i + 1
    t_vec = np.array([i for i in range(0, 10 ** 4)])
    plt.plot(t_vec, 1 / (t_vec + 1 / 0.25), '--', label = r'$MF: \alpha = 1$', color = 'k', linewidth = 2)

    plt.xlabel(r'$t$', fontsize=25)
    plt.ylabel(r'$\rho$', fontsize=25)
    plt.legend(loc = 'best')
    plt.tick_params(labelsize=20)
    plt.tight_layout()

def show_sepereted():
    plt.figure()
    d_vec = [2, 3]
    color_list = ['r', 'b']
    i = 0
    for d in d_vec:
        j = 0
        path = "/home/bnaya/Desktop/chimestry/results/mixed/d" + str(d) + "/*"
        for f in glob.glob(path):
            data = np.loadtxt(f)
            x, y = zip(*data)
            if j == 0:
                plt.loglog(x, y, '-o', color=color_list[i], label = r'$mixed: d = $' + str(d))
            else:
                plt.loglog(x, y, '-o', color=color_list[i])

            if j == 1:
                break
            j = j + 1
        i = i + 1

    d_vec = [2, 3]
    color_list = ['r', 'b']
    i = 0
    for d in d_vec:
        j = 0
        path = "/home/bnaya/Desktop/chimestry/results/sepereted/d" + str(d) + "/*"
        for f in glob.glob(path):
            data = np.loadtxt(f)
            x, y = zip(*data)
            if j == 0:
                plt.loglog(x, y, '-s', color=color_list[i], label = r'$separated: d = $' + str(d))
            else:
                plt.loglog(x, y, '-s', color=color_list[i])

            if j == 1:
                break
            j = j + 1
        i = i + 1
    t_vec = np.array([i for i in range(0, 10 ** 4)])
    plt.plot(t_vec, 1 / (t_vec + 1 / 0.25), '--', label = r'$MF: \alpha = 1$', color = 'k', linewidth = 2)
    plt.xlabel(r'$t$', fontsize=25)
    plt.ylabel(r'$\rho$', fontsize=25)
    plt.legend(loc = 'best')
    plt.tick_params(labelsize=20)
    plt.tight_layout()