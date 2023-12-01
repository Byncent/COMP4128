import random
import subprocess

def gen_input():
    s = ""
    #T = random.randint(1, 1)
    T = 1
    s += f"{str(T)}\n"
    for _ in range(T):
        n = random.randint(1, 3)
        s += f"{n}\n"
        for _ in range(n):
            s += f"{str(random.randint(1, 1000000000))} "
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
        solution += f"{str(res)}\n"
    return solution.rstrip()

MAX_ITER = 100
EXE = "./A"

if __name__ == "__main__":
    for i in range(MAX_ITER):
        s = gen_input()
        got = subprocess.run(EXE, input=s, capture_output=True, text=True).stdout.strip()
        ans = brute_force(s)
        if got != ans:
            print(f"Failed\n")
            print(f"Input: \n{s}\n")
            print(f"Expected: \n{ans}\n")
            print(f"Got: \n{got}")
            exit(1)
        else:
            print("Passed")