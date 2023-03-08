def mul(a, b, m):
    c = [[0 for j in range(len(b[0]))] for i in range(len(a))]
    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(a[0])):
                c[i][j] += a[i][k] * b[k][j]
            c[i][j] %= m
    return c

def binpow(a, n, m):
    res = [[1, 0], [0, 1]]
    while n > 0:
        if n % 2 == 1:
            res = mul(res, a, m)
        a = mul(a, a, m)
        n = n // 2

    return res

def solve():
    n = int(input())
    k = int(input())
    m = int(input())

    matrix = [[0, (k - 1) % m], [1, (k - 1) % m]]

    matrix = binpow(matrix, n, m)

    ans = (matrix[0][0] + (k - 1) * matrix[1][0]) % m

    print(ans)

solve()

#import sys
#inp = sys.stdin.readline
#n, k = map(int, inp().split())
#a = list(map(int, inp().split()))
# change flobal var in function
# global a
# a = 2
