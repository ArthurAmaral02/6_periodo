import numpy as np

w = np.array([[10, 0.6]]).T
e = np.array([[0.2, -0.1, -0.4, 0.6]]).T

x0 = np.ones((4, 1))
x1 = np.array([[10, 20, 40, 50]]).T

########################################################
X = np.column_stack((x0, x1))
y = X @ w + e

N = X.shape[0]
D = X.shape[1]
T_max = 1000000
e_min = .1
lr = 0.00001

w = np.zeros((D, 1))
t = 0
while True:

    e = (1/N) * (w.T @ X.T @ X @ w - 2*w.T @ X.T @ y + y.T @ y)
    dedw = (2/N) * (X.T @ X @ w - X.T @ y)
    dedw_norm = np.sqrt(dedw.T @ dedw)
    if e <= e_min or t >= T_max:
        break

    
    w = w - lr * dedw
    
    # print(f"Iteration: {t}, Error: {e}, Weights: {w}, dedw: {dedw_norm}")

    t = t + 1

r = y - X@w
print(f"Iteration: {t}, Error: {e}, Weights: {w}, Residuals: {r}, dedw: {dedw_norm}")
