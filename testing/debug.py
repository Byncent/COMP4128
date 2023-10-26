from random import randint
import subprocess

LIMA = 5
LIMM = 5
LIMQ = 5
LIMC = 5

randint(0, 0)

def gen():
    res = ""
    n = randint(1, LIMA)
    res += f"{str(n)}\n"
    arr = []
    for _ in range(n):
        arr.append(randint(0, LIMQ))

    arr.sort(reverse=True)

    for item in arr:
        res += f"{str(item)} "

    res += '\n'

    if n == 1:
        res += "0\n"
        return res
    
    m = randint(n-1, LIMM)
    res += f"{str(m)}\n"


    i = 0
    while (i < m):
        print(f"i = {i}")
        a = randint(1, n-1)
        b = randint(a, n)
        if arr[a-1] <= arr[b-1]:
            continue
        c = randint(1, LIMC)
        res += f"{a} {b} {c}\n"
        i += 1

    return res



EXE = "./A"
TEST = "./test"

if __name__ == "__main__":
    for i in range(100):
        print(f"iter: {i}")
        s = gen()
        got = subprocess.run(EXE, input=s, capture_output=True, text=True).stdout.strip()
        ans = subprocess.run(TEST, input=s, capture_output=True, text=True).stdout.strip()
        if got != ans:
            f = open("testcase.txt", "w")
            f.write(s)
            f.close()
            print(f"Failed:")
            print(f"Input '{s}'")
            print(f"Expected '{ans}'")
            print(f"Got '{got}'")
            exit(1)