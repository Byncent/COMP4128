from random import randint
import subprocess

limn = 5
limm = 10

randint(0, 0)

def gen():
    res = ""
    n = randint(2, limn)
    res += f"{str(n)} "
    m = randint(n-1, n * (n-1)/2)
    res += f"{str(m)} \n"

    pairs = {1:[]}

    i = 0

    while(i < m):
        a = randint(1, n)
        b = randint(1, n)

        if a not in pairs:
            print("case 1")
            pairs[a] = [b]



        if b not in pairs:
            print("case 3")
            pairs[b] = [a]

            

        if(a == b) or (b in pairs[a]) or (a in pairs[b]):
            continue
            
        pairs[a].append(b)
        pairs[b].append(a)

        res += f"{str(a)} {str(b)}\n"
        i+= 1

    return res



EXE = "./C"
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