"""
Task: given rain probability array [p0,...,p(m-1)] for m days and int n
What is probability that it rains in at least n days?

Solution: Let q(n, m) be the probability that it rains at least n days from day 0 to day m.
Then: q(n, m) = p(m) * q(n-1, m-1) + (1-p(m)) * q(n, m-1)
"""

from typing import Sequence
import numpy as np

def prob_rain_more_than_n(p: Sequence[float], n: int) -> float:
    m = len(p)
    # Edge cases
    if n > m:
        return 0.0
    if n <= 0:
        return 1.0
    q = np.zeros(shape=(n+1, m)) #q[i][j]: Prob it rains for >= i days from day 0 to j

    # Base cases
    # It always rain for at least 0 day
    for j in range(0, m):
        q[0][j] = 1

    q[1][0] = p[0] # Probability that the first day rains
    # q[2...][0] = 0 # It can't rain for more than 2 days from day 0 to 0
    
    # Fill the table
    for j in range(1, m):
        for i in range(1, n+1):
            q[i][j] = p[j]*q[i-1][j-1] + (1-p[j])*q[i][j-1]
    print(q) # Comment out to disable debugging
    return q[n][m-1]

p = [0.7]
n = 1
print(prob_rain_more_than_n(p, n))
