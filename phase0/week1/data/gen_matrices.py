"""Generate a test input for the matmul project.

File format (plain text, whitespace-separated):
    n
    n rows of A (n numbers each)
    n rows of B (n numbers each)

Usage: python3 gen_matrices.py N OUTFILE [--ints]
"""
import random
import sys

n = int(sys.argv[1])
out = sys.argv[2]
ints = "--ints" in sys.argv
random.seed(42)  # same file every time -> Python and C++ results comparable

def val():
    return str(random.randint(0, 9)) if ints else f"{random.uniform(-1, 1):.6f}"

with open(out, "w") as f:
    f.write(f"{n}\n")
    for _ in range(2 * n):  # A then B
        f.write(" ".join(val() for _ in range(n)) + "\n")
