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
results = {algorithm: {'best': [], 'random': [], 'worst': []} for algorithm in algorithms}
expected = {
        'insertionSort': {'best': 'n',     'random': 'n^2',   'worst': 'n^2'},
        'selectionSort': {'best': 'n^2',   'random': 'n^2',   'worst': 'n^2'},
        'quickSort':     {'best': 'nlogn', 'random': 'nlogn', 'worst': 'nlogn'},
        'mergeSort':     {'best': 'nlogn', 'random': 'nlogn', 'worst': 'nlogn'},
        'heapSort':      {'best': 'nlogn', 'random': 'nlogn', 'worst': 'n^2'},
        }

def compile():
    cmd = "gcc -Wl,--stack,32777216 -O0 src/index.c -o index"
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

def plot(data, algorithm, case):
    n_values = [item[0] for item in data]
    t_values = [item[1] for item in data]
    plt.plot(n_values, t_values, marker='o', linestyle='-', color='b')
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title('T(n) x n Plot for ' + algorithm + ' ' + case)
    plt.savefig('tn_plot_' + algorithm + '_' + case + '.png')
    plt.close()

def get_iters(algorithm, case):
    if expected[algorithm][case] == 'nlogn':
        iterations = 2_000_000
        step=int(iterations/15)
    else:
        iterations = 200000
        step=int(iterations/10)
    return iterations, step

compile()

for algorithm in algorithms:
    for case in ['worst', 'random', 'best']:
        iterations, step = get_iters(algorithm, case)
        for n in range(step, iterations, step):
            output = grab(n, case, algorithm)
            results[algorithm][case].append((n, output))
        plot(results[algorithm][case], algorithm, case)
