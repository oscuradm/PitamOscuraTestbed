#!/usr/bin/env python3

import csv
import sys

import numpy as np
import matplotlib.pyplot as plt


def ImportCSV(file):
    
    LineNumber = 0
    
    BinContents = []
    
    
    with open(file, newline='\n') as csvfile:
        csvreader = csv.reader(csvfile, delimiter=',')
        for row in csvreader:
            if LineNumber>6:
                #print(row)
                BinContents.append(int(row[0]))
            LineNumber+=1
            
    return BinContents


def PlotBC(BinContents, MinVal, MaxVal):
    
    n_entries = len(BinContents)
    x_axis = np.linspace(MinVal, MaxVal, n_entries)
    
    plt.plot(x_axis, BinContents)
    plt.xlabel("Energy bins keV")
    plt.ylabel("Cts")
    plt.show();



if __name__ == '__main__':
    filename = sys.argv[1]
    BinContents = ImportCSV(filename)
    PlotBC(BinContents, 0, 8)