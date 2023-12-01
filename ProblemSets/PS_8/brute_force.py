
T = int(input())
for _ in range(T):
    s = []
    n = int(input())
    for _ in range(n):
        s.append(int(input()))
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
    print(res)