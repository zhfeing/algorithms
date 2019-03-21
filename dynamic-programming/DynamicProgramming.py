# coding=utf-8
import numpy as np
import random
import math
from matplotlib import pyplot

# batch gradient descent algorithm
M = 5  # the size of the train data
x = np.ndarray(M)
y = np.ndarray(M)
for i in range(M):
    x[i] = random.randrange(0, 10*M)
    y[i] = 2 * x[i] + random.randrange(-math.floor(math.sqrt(M)),
                                       math.floor(math.sqrt(M)))

print(x, y)
pyplot.figure(1)
pyplot.plot(x, 2 * x, 'b')
pyplot.scatter(x, y, c='r')

# begin the algorithm
theta = np.ndarray(2)


# initial
class BatchGradientDescentAlgorithm:
    def __init__(self, num_theat, x_list, y_ndarray):
        '''theta_0 is not added in theta by default,
        so num_theat must contain theta_0'''
        self.__num_theat = num_theat
        self.__theta = np.ndarray(num_theat)
        self.__alpha = 0.0001
        self.__x_list = x_list
        self.__y_ndarray = y_ndarray
        self.__this_generation = 0
        self.__error = 0.001
        self.__last_h = 0
        if len(x_list) != len(y_ndarray):
            print('error: list length is not equal')
        else:
            self.__num_data = len(x_list)
        for i in range(num_theat):
            self.__theta[i] = 0

    def h(self, x):
        tmp = 0
        for i in range(self.__num_theat):
            tmp += self.__theta[i] * x[i]
        return tmp

    def set_theta_i(self, theta_i, i):
        if i >= self.__num_theat or i < 0:
            return None
        else:
            self.__theta[i] = theta_i

    def get_theta(self):
        return self.__theta

    def next_iteration(self):
        self.__theta -= self.__alpha * \
                        (self.h(self.__x_list[self.__this_generation]) -
                         self.__y_ndarray[self.__this_generation]) * \
                        self.__x_list[self.__this_generation]
        print(self.__theta)
        if self.__this_generation != 0:
            if abs(self.h(self.__x_list[self.__this_generation]) -
                           self.__last_h) < self.__error:
                self.__last_h = self.h(self.__x_list[self.__this_generation])
                self.__this_generation += 1
                return True
            else:
                self.__last_h = self.h(self.__x_list[self.__this_generation])
                self.__this_generation += 1
                return False
        else:
            self.__last_h = self.h(self.__x_list[self.__this_generation])
            self.__this_generation += 1
            return False

# begin the iteration
x_list = []
for i in range(M):
    t = np.ndarray(2)
    t[0] = 1
    t[1] = x[i]
    x_list.append(t)

BGDA = BatchGradientDescentAlgorithm(2, x_list, y)
i = 0
while not BGDA.next_iteration() and i < M - 1:
    i += 1
if i == M - 1:
    print('not converge')

# pyplot.show()
