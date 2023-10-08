from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import numpy as np

def fit_and_plot(data, fitting_function, algorithm, case):
    n_values = np.array([item[0] for item in data])
    t_values = np.array([item[1] for item in data])

    # Use curve_fit to fit the specified function to the data
    params, covariance = curve_fit(fitting_function, n_values, t_values)
    fitted_params = tuple(params)
    fit_curve = fitting_function(n_values, *fitted_params)

    # Plotting the original data and the fitted curve
    plt.plot(n_values, t_values, marker='o', linestyle='-', color='b', label='Original Data')
    plt.plot(n_values, fit_curve, linestyle='--', color='r', label='Fitted Curve')

    # Adding labels and title
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title('T(n) x n Plot for ' + algorithm + ' ' + case + ' with Curve Fitting')
    # Show the legend
    plt.legend()

    # Save the plot to a file
    plt.savefig('tn_plotFit_' + algorithm + '_' + case + '.png')
    plt.close()

def quadratic_function(n, a, b, c):
    return a*n**2 + b*n + c

def main():
    data = [(20000, 0.419393875), (40000, 1.64236075), (60000, 3.5711945), (80000, 6.38446125), (100000, 9.93483875), (120000, 14.348628625), (140000, 19.487868625), (160000, 25.574401375), (180000, 32.569879625) ]
    fit_and_plot(data, quadratic_function, 'QuadraticAlgo', 'Worst')

main()
