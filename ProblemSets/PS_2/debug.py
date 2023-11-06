import random
import subprocess

def options(s, t, u):
    if not s and not t:
        yield u

    else:
        # s -> t
        if s:
            s1 = s[1:]
            t1 = t + s[0]
            yield from options(s1, t1, u)

        # t -> u
        if t:
            t2 = t[:-1]
            u2 = u + t[-1]
            yield from options(s, t2, u2)


def solve(s):
    return min(options(s, '', ''))

MAX_LEN = 10
CASES_PER_LEN = 30
EXE = "./A_v1"

if __name__ == "__main__":
    for l in range(1, MAX_LEN):
        for case in range(CASES_PER_LEN):
            s = ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=l))
            got = subprocess.run(EXE, input=s, capture_output=True, text=True).stdout.strip()
            ans = solve(s)
            if got != ans:
                print(f"Failed:")
                print(f"Input '{s}'")
                print(f"Expected '{ans}'")
                print(f"Got '{got}'")
                print("Character by character:")
                for i, s in enumerate(got):
                    print(f"{i}th character is {s} with ascii value {ord(s)}")
                exit(1)