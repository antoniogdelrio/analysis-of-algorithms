import subprocess
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
results = {algorithm: {'best': [], 'random': [], 'worst': []} for algorithm in algorithms}
expected = {
        'insertionSort': {'best': 'n',     'random': 'n^2',   'worst': 'n^2'},
        'selectionSort': {'best': 'n^2',   'random': 'n^2',   'worst': 'n^2'},
        'quickSort':     {'best': 'nlogn', 'random': 'nlogn', 'worst': 'n^2'},
        'mergeSort':     {'best': 'nlogn', 'random': 'nlogn', 'worst': 'nlogn'},
        'heapSort':      {'best': 'nlogn', 'random': 'nlogn', 'worst': 'nlogn'},
        }

def compile():
    cmd = "gcc -Wl,--stack,32777216 -O0 src/index.c -o index"
    subprocess.run(cmd.split())

def grab(iterations, case, algorithm):
    print(algorithm
          + "\t n=" + str(iterations) 
          + "\t" + case, end='\t')
    cmd = "./index " + str(iterations) + " " + case + " " + algorithm
    output = subprocess.run(cmd.split(), 
                            capture_output=True, text=True).stdout
    output = output.split(', ')[1:-1]
    output = [float(string) for string in output]
    output = statistics.mean(output)
    print('T(n)=' + str(output))
    return output

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

    for algorithm in algorithms:
        for case in ['worst', 'random', 'best']:
            iterations, step = get_iters(algorithm, case)
            for n in range(step, iterations, step):
                output = grab(n, case, algorithm)
                results[algorithm][case].append((n, output))

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
                    results[algorithm][case],
                    selected_function,
                    algorithm,
                    case)

if __name__ == "__main__":
    main()
