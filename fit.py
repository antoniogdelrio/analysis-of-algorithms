from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import numpy as np

def firstLetterUppercase(input_str):
    return input_str[0].upper() + input_str[1:] if input_str else input_str

def pretty_params(function, coefficients):
    formatted_str = ""

    if function == quadratic_function:
        formatted_str = f"{coefficients[0]:.2e}n² + {coefficients[1]:.2e}n + {coefficients[2]:.2e}"
    elif function == n_log_n_function:
        # Handle n log n function
        formatted_str = f"{coefficients[0]:.2e}n log(n) + {coefficients[1]:.2e}"
    elif function == linear_function:
        # For linear function, only show terms for n
        formatted_str = f"{coefficients[0]:.2e}n + {coefficients[1]:.2e}"
    else:
        formatted_str = 'Fitted Curve'

    return formatted_str

def fit_and_plot(data, fitting_function, algorithm, case):
    n_values = np.array([item[0] for item in data])
    t_values = np.array([item[1] for item in data])

    # Use curve_fit to fit the specified function to the data
    params, covariance = curve_fit(fitting_function, n_values, t_values)
    fitted_params = tuple(params)
    fit_curve = fitting_function(n_values, *fitted_params)

    # Plotting the original data and the fitted curve
    plt.plot(n_values, t_values, marker='o', linestyle='-', color='b', label='Original Data')
    plt.plot(n_values, fit_curve, linestyle='--', color='r', 
             label=pretty_params(fitting_function, fitted_params))

    # Adding labels and title
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title('T(n) x n Plot for '
              + firstLetterUppercase(algorithm)
              + ' ' + case
              + ' with Curve Fitting')
    # Show the legend
    plt.legend()

    # Save the plot to a file
    plt.savefig('tn_plotFit_' + algorithm + '_' + case + '.png')
    plt.close()

def quadratic_function(n, a, b, c):
    return a*n**2 + b*n + c

def n_log_n_function(n, a, b):
    return a*n*np.log(n) + b

def linear_function(n, a, b):
    return a * n + b
