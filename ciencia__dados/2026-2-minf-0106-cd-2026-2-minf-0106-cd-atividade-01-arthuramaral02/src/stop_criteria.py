from __future__ import annotations
from typing import List
import src.algorithms as al

import abc

class StopCriteria(abc.ABC):

    
    @abc.abstractmethod
    def isFinished(self, alg: al.Algorithm) -> bool:
        """Implement stop criterium"""

