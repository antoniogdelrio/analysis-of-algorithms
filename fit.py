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

def n_log_n_function(n, a, b):
    return a*n*np.log(n) + b

def linear_function(n, a, b):
    return a * n + b

def main():
    data = [(20000, 0.419393875), (40000, 1.64236075), (60000, 3.5711945), (80000, 6.38446125), (100000, 9.93483875), (120000, 14.348628625), (140000, 19.487868625), (160000, 25.574401375), (180000, 32.569879625) ]
    fit_and_plot(data, quadratic_function, 'QuadraticAlgo', 'Worst')

    data = [ (133333, 0.010812125), (266666, 0.022565375), (399999, 0.034805375), (533332, 0.04693975), (666665, 0.0597295), (799998, 0.07232325), (933331, 0.085462875), (1066664, 0.09750125), (1199997, 0.11764575), (1333330, 0.12459287499999999), (1466663, 0.137640875), (1599996, 0.15102025), (1733329, 0.165309875), (1866662, 0.18934275), (1999995, 0.216649) ]
    fit_and_plot(data, n_log_n_function, 'LogAlgo', 'Best')

    data = [ (20000, 5.525e-05), (40000, 0.000110625), (60000, 0.000169875), (80000, 0.00023475), (100000, 0.00028074999999999997), (120000, 0.00032362499999999997), (140000, 0.00038462500000000004), (160000, 0.00043387499999999996), (180000, 0.000498875) ]
    fit_and_plot(data, linear_function, 'LinearAlgo', 'Best')

main()
