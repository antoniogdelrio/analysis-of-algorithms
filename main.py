from ctypes import *
import subprocess
import os
import statistics

# Parameters
algorithms = [
        'insertionSort',
        'selectionSort',
        'quickSort',
        'mergeSort',
        'heapSort']
iterations = 1000
results_best = {algorithm: [] for algorithm in algorithms}
results_avg = {algorithm: [] for algorithm in algorithms}
results_worst = {algorithm: [] for algorithm in algorithms}

def compile():
    cmd = "gcc -O0 src/index.c -o index"
    subprocess.run(cmd.split())

def grab(iterations, case, algorithm):
    cmd = "./index " + str(iterations) + " " + case + " " + algorithm
    output = subprocess.run(cmd.split(), 
                            capture_output=True, text=True).stdout
    output = output.split(', ')[1:-1]
    output = [float(string) for string in output]
    output = statistics.mean(output)
    return output

compile()

output = grab(1000, 'worst', 'insertionSort')
results_worst['insertionSort'].append((1000, output))

print(output)
print(results_worst)
