from ctypes import *
import subprocess
import os

# Classes das Análises
class SortAnalysis:
    """Classe para cada análise de algoritmo"""
    def __init__(self, algorithm, n, strategy):
        self.algorithm = algorithm
        self.strategy = strategy
        self.n = n
        self.results = []


# Compilação dos arquivos .c
dir_path = os.getcwd()

source_file = os.path.join(dir_path, "index.c")
so_file = os.path.join(dir_path, "index.so")

if os.path.exists(so_file):
    os.remove(so_file)

try:
    subprocess.check_call(
        ["gcc", "-O0", "-shared", "-o", so_file, "-fPIC", source_file]
    )
    print("Compilation successful.")
except subprocess.CalledProcessError:
    print("Compilation failed.")

functions = CDLL(so_file)
sort_analysis = functions.sortAnalysis

# Análises que serão realizadas
analyses = []
#analyses.append(SortAnalysis(functions.insertionSort, 100000, 2))
#analyses.append(SortAnalysis(functions.selectionSort, 100000, 2))
#analyses.append(SortAnalysis(functions.quickStarter, 100000, 2))
analyses.append(SortAnalysis(functions.mergeStarter, 100000, 2))

# Realização das Análises

for analysis in analyses:

    analysis.results = []

    #analysys[i].algorithm.argtypes = [c_int, c_int]
    sort_analysis.restype = POINTER(c_float * 3)

    analysis.results = sort_analysis(analysis.n, analysis.strategy, analysis.algorithm).contents

    print(str(analysis.results[0]) + " "
        + str(analysis.results[1]) + " "
        + str(analysis.results[2]))
