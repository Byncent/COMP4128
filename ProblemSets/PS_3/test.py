n = int(input())
m = int(input())
k = int(input())

a = [0] * n
colors = [i for i in range(m)]

sol = [[0]]

def rec(arr):
    if(len(arr) == n):
        sol.append(arr)
        return

    for color in colors:
        dup = arr
        rec(dup.append(color))

