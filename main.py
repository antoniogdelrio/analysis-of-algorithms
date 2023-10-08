from ctypes import *
import subprocess
import os
import statistics
import matplotlib.pyplot as plt

# Parameters
algorithms = [
        'insertionSort',
        'selectionSort',
        'quickSort',
        'mergeSort',
        'heapSort']
iterations = 200000
results_best = {algorithm: [] for algorithm in algorithms}
results_avg = {algorithm: [] for algorithm in algorithms}
results_worst = {algorithm: [] for algorithm in algorithms}

def compile():
    cmd = "gcc -O0 src/index.c -o index"
    subprocess.run(cmd.split())

def grab(iterations, case, algorithm):
    print("Running " + algorithm
          + " with n=" + str(iterations) 
          + " and "
          + case + " case.")
    cmd = "./index " + str(iterations) + " " + case + " " + algorithm
    output = subprocess.run(cmd.split(), 
                            capture_output=True, text=True).stdout
    output = output.split(', ')[1:-1]
    output = [float(string) for string in output]
    output = statistics.mean(output)
    return output

def plot(data):
    n_values = [item[0] for item in data]
    t_values = [item[1] for item in data]
    plt.plot(n_values, t_values, marker='o', linestyle='-', color='b')
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title('T(n) x n Plot')
    plt.savefig('tn_plot.png')
    plt.close()

compile()

step=int(iterations/50)
for n in range(step, iterations, step):
    output = grab(n, 'worst', 'insertionSort')
    results_worst['insertionSort'].append((n, output))

plot(results_worst['insertionSort'])
