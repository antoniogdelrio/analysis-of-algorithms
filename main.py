import subprocess
import resource
import sys
import os
import statistics
import matplotlib.pyplot as plt
import fit

# Parameters
algorithms = [
        'insertionSort',
        'selectionSort',
        'quickSort',
        'mergeSort',
        'heapSort']
res_mean = {algorithm: {'best': [], 'random': [], 'worst': []} for algorithm in 
algorithms}
res_sd = {algorithm: {'best': [], 'random': [], 'worst': []} for algorithm in algorithms}
expected = {
        'insertionSort': {'best': 'n',     'random': 'n^2',   'worst': 'n^2'},
        'selectionSort': {'best': 'n^2',   'random': 'n^2',   'worst': 'n^2'},
        'quickSort':     {'best': 'nlogn', 'random': 'nlogn', 'worst': 'n^2'},
        'mergeSort':     {'best': 'nlogn', 'random': 'nlogn', 'worst': 'nlogn'},
        'heapSort':      {'best': 'nlogn', 'random': 'nlogn', 'worst': 'nlogn'},
        }

def compile():
    cmd = "gcc -O0 src/index.c -o index"
    subprocess.run(cmd.split())

def set_stack_limit(new_gb_limit=10.0):
    new_bytes_limit = int(new_gb_limit * 1024 * 1024 * 1024)  # Convert GB to bytes
    resource.setrlimit(
            resource.RLIMIT_STACK,
            (new_bytes_limit, resource.RLIM_INFINITY))

    current_stack_limit_bytes, _ = resource.getrlimit(resource.RLIMIT_STACK)
    current_stack_limit_gb = current_stack_limit_bytes / (1024 * 1024 * 1024)
    print(f"Stack size limit: {current_stack_limit_gb} GB")

def grab(iterations, case, algorithm):
    print(algorithm
          + "\t n=" + str(iterations) 
          + "\t" + case, end='\t')
    cmd = "./index " + str(iterations) + " " + case + " " + algorithm
    output = subprocess.run(cmd.split(), 
                            capture_output=True, text=True).stdout
    output = output.split(', ')[1:-1]
    output = [float(string) for string in output]
    mean = statistics.mean(output)
    sd = statistics.stdev(output)
    print('T(n)={:.4f}\tSD={:.4f}'.format(mean, sd))
    return mean, sd

def get_iters(algorithm, case):
    if expected[algorithm][case] == 'nlogn':
        iterations = 2_000_000
        step=int(iterations/15)
    else:
        iterations = 200000
        step=int(iterations/10)
    return iterations, step

def main():
    compile()
    set_stack_limit(10.0)

    for algorithm in algorithms:
        for case in ['worst', 'random', 'best']:
            iterations, step = get_iters(algorithm, case)
            for n in range(step, iterations, step):
                mean, sd = grab(n, case, algorithm)
                res_mean[algorithm][case].append((n, mean))
                res_sd[algorithm][case].append((n, sd))

            if expected[algorithm][case] == 'n^2':
                selected_function = fit.quadratic_function
            elif expected[algorithm][case] == 'nlogn':
                selected_function = fit.n_log_n_function
            elif expected[algorithm][case] == 'n':
                selected_function = fit.linear_function
            else:
                print("Error while selecting function")
                return -1

            fit.fit_and_plot(
                    res_mean[algorithm][case],
                    res_sd[algorithm][case],
                    selected_function,
                    algorithm,
                    case)

if __name__ == "__main__":
    main()
