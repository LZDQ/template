import numpy as np
from numpy.typing import NDArray

def solve_eq_square_mod(a: NDArray[np.integer], b: NDArray[np.integer], p: int):
    """ Given matrix a: nxn, vector b: n and mod p, find x: n s.t. Ax=b """
    a = np.copy(a) % p
    b = np.copy(b) % p
    assert a.shape[0] == a.shape[1], 'A must be square'
    assert p < 2**32, 'p must be within uint32'
    n = a.shape[0]
    a = np.concat((a, b.reshape(-1, 1)), axis=1) % p
    for i in range(n):
        if a[i][i] == 0:
            for j in range(i+1, n):
                if a[j][i]:
                    a[[i, j]] = a[[j, i]]
                    break
            if a[i][i] == 0:
                raise ValueError
        a[i] = a[i] * pow(a[i][i], p-2, p) % p
        for j in range(i+1, n):
            if a[j][i]:
                a[j] = (a[j] - a[j][i] * a[i]) % p
    for i in reversed(range(n)):
        for j in range(i+1, n):
            a[i] = (a[i] - a[j] * a[i][j]) % p

    return a[:,n]

def solve_inv_mod(a: NDArray[np.integer], p: int):
    """ Given matrix a: nxn and mod p, return inverse. """
    a = np.copy(a) % p
    assert a.shape[0] == a.shape[1], 'A must be square'
    assert p < 2**32, 'p must be within uint32'
    n = a.shape[0]
    a = np.concat((a, np.eye(n, dtype=int)), axis=1)
    
    for i in range(n):
        if a[i][i] == 0:
            for j in range(i+1, n):
                if a[j][i]:
                    a[[i, j]] = a[[j, i]]
                    break
            if a[i][i] == 0:
                raise ValueError
        a[i] = a[i] * pow(a[i][i], p-2, p) % p
        for j in range(i+1, n):
            if a[j][i]:
                a[j] = (a[j] - a[j][i] * a[i]) % p
    for i in reversed(range(n)):
        for j in range(i+1, n):
            a[i] = (a[i] - a[j] * a[i][j]) % p
    return a[:,n:]

