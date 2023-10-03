def recursion(num, sols, curr, blocksRem, blocksTotal):
    if len(curr) == blocksTotal:
        if num == 0:
            sols.append(curr)
        return

    for i in range(1, num+1):
        dup = [j for j in curr]
        dup.append(i)
        recursion(num - i, sols, dup, blocksRem - 1, blocksTotal)


if __name__ == "__main__":
    n = int(input())
    k = int(input())

    sols = []
    curr = []
    recursion(n, sols, curr, k+1, k+1)

    print(len(sols))