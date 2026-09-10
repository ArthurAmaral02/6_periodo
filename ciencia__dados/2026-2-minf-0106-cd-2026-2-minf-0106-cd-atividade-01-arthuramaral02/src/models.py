import numpy as np
import scipy.stats as st
import abc
import src.optimizers as opt

class Model(abc.ABC):

    def __init__(self) -> None:
        super().__init__()
        
    
    @abc.abstractmethod
    def predict() -> np.ndarray:
        """Implement the predict method"""
        
    @property
    def w(self):
        return self._w

    @w.setter
    def w(self, value):
        self._w = value

