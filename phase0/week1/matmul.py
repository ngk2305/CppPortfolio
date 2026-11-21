import sys
import time

def main():
    with open(sys.argv[1]) as f:
        lines = f.readlines()   # list of strings, one per line, each ending in "\n"
    n = int (lines[0])
    A = []
    B = []
    for line in range(1,n+1):
        a = [float(x) for x in lines[line].split()]
        A.append(a)
    for line in range(n+1,2*n+1):
        b = [float(x) for x in lines[line].split()]
        B.append(b)
   
    
    C = [[0 for i in range(n)] for j in range(n)]
    before = time.perf_counter()
    for i in range(n):
        for k in range(n):
            for j in range(n):
                C[i][j] += A[i][k] * B[k][j]
    after = time.perf_counter()
    print(after-before)
    return 0

if __name__ == "__main__":
    main()
    