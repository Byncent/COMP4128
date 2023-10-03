def rec(arr, sols, colors, n, m, k):
    if len(arr) == n:
        counter = 0
        for i in range(1, n):
            if arr[i] != arr[i-1]:
                counter += 1
        if counter == k:
            sols.append(arr)
        return 0

    
    for color in colors:
        dup= [i for i in arr]
        dup.append(color)
        rec(dup, sols, colors, n, m, k)

if __name__ == "__main__":
    n = int(input())
    m = int(input())
    k = int(input())

    sols= []

    colors = [i for i in range(m)]
    a = []
    rec(a, sols, colors, n, m, k)
    
    print("solutions: ")
    for sol in sols:
        for item in sol:
            print(item, end=" ")
        print("")
    print(f"count: {len(sols)}")
