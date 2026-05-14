import numpy as np


def est_pi(n):
    # generate n x 2 array of uniformly random numbers
    points = np.random.uniform(-1, 1, (n, 2))
    # square each point
    distances = np.sum(points**2, axis=1)  # sum rows / collapse column
    hits = np.count_nonzero(distances <= 1.0)
    # counting how many elements satisfy inequality
    # True is 1 and False is 0, so counting # of True's
    return 4 * (hits / n)


print(f"Pi Estimate: {est_pi(100000)}")
