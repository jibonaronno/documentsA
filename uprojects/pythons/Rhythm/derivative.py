#finite difference approximation formulas
import numpy
import matplotlib.pyplot as plott
import pprint
import math

def f(x):
    return numpy.tan(x)

def f_diff(x):
    return 1/numpy.cos(x)**2

def centered(x, h):
    return (f(x+h) - f(x-h))/(2*h)

def forward(x, h):
    return (f(x+h)-f(x))/h

def _forward(x, h):
    return (math.sin(x+h)-math.sin(x))/h

x0 = 0.2

h_vector = [10**(-temp) for temp in numpy.arange(0, 17, 0.1)]
x_vector = [xvalue for xvalue in numpy.arange(0, numpy.pi, 0.1)]
sin_arr = numpy.zeros(len(x_vector))
deriv = numpy.zeros(len(x_vector))
deriv2 = numpy.zeros(len(x_vector))

for index, _sin in enumerate(x_vector):
    sin_arr[index] = math.sin(_sin)

vector_len = len(sin_arr)
for index, _sin in enumerate(sin_arr):
    if index < (vector_len - 1):
        deriv[index] = forward(_sin, sin_arr[index+1])
        deriv2[index] = _forward(x_vector[index], x_vector[index+1])

plott.plot(x_vector, sin_arr, label="_Sin_")
plott.plot(x_vector, deriv2, label="_Derivative")

#plott.loglog(x_vector, sin_arr, label="__Sin__")

'''
forward_res = numpy.zeros(len(h_vector))
centered_res = numpy.zeros(len(h_vector))
true_res = numpy.zeros(len(h_vector))

for index, _h in enumerate(h_vector):
    forward_res[index] = forward(x0, _h)
    centered_res[index] = centered(x0, _h)
    true_res[index] = f_diff(x0)

x_array = [idx for idx in range(len(h_vector))]
x_arr = [idxx for idxx in numpy.arange(0, 17, 0.1)]

plott.figure(dpi=100)
#plott.loglog(x_array, true_res, label="true")
#plott.loglog(x_array, forward_res, label="Forward")
#plott.loglog(h_vector, abs(forward_res - true_res), label="Forward-true")
#plott.loglog(h_vector, abs(centered_res - true_res), label="Centered")
plott.loglog(x_arr, h_vector, label="h_vector")
'''
plott.grid()
plott.xlabel = "h"
plott.ylabel = "Absolute Difference"
plott.legend()
plott.show()

