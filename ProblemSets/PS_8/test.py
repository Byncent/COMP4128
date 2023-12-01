import random
import subprocess

def gen_input():
    s = ""
    T = random.randint(1, 5)
    s += f"{str(T)}\n"
    for _ in range(T):
        n = random.randint(1, 10)
        s += f"{n}\n"
        for _ in range(n):
            s += f"{str(random.randint(1, 10))} "
        s += '\n'
    return s.rstrip()

def brute_force(set_nums):
    i = 0
    inputs = [int(item) for item in set_nums.split()]
    solution = ""

    T = int(inputs[i])
    i += 1
    for _ in range(T):
        s = []
        n = inputs[i]
        i += 1
        for _ in range(n):
            s.append(inputs[i])
            i += 1
        subsets = [[]]
        for element in s:
            temps = []
            for subset in subsets:
                temp = subset.copy()
                temp.append(element)
                temps.append(temp)
            for temp in temps:
                subsets.append(temp)
        subsets.sort()
        res = 0
        for subset in subsets:
            if(subset == []):
                continue
            res += max(subset) - min(subset)
            res = res%(1e9+7)
        solution += f"{str(res)}\n"
    return solution.rstrip()

s = """4
2
1 2
3
1 2 3
4
1 2 3 4
3
1 2 2"""
print(brute_force(s))