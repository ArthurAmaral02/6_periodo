import numpy as np
import scipy.stats as st
from typing import Tuple

class DataGenerator():
    def __init__(self, sample_size, weights, x_min, x_max):
        self.sample_size = sample_size
        self.weights = weights
        self.x_min = x_min
        self.x_max = x_max
 
    def get_data(self):
        X = np.linspace(self.x_min, self.x_max, self.sample_size).reshape(-1, 1)
 
        X_bias = np.column_stack((np.ones((self.sample_size, 1)), X))
 
        noise = np.random.normal( 0, 1, size=(self.sample_size, 1) )
        
        y = X_bias @ self.weights + noise
 
        return X, y
