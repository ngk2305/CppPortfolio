"""Run every matmul implementation on the same input file and record their times.

Each program prints its own elapsed time; this script just runs them, pulls
out the number, and appends one row per run to a CSV.

Usage (from anywhere):
    python3 phase0/week1/run_bench.py phase0/week1/data/big_512.txt
    python3 phase0/week1/run_bench.py data/small_3.txt --only ijk ikj
    python3 phase0/week1/run_bench.py data/big_512.txt --csv results/my_runs.csv
"""
import argparse
import csv
import datetime
import re
import subprocess
import sys
from pathlib import Path

WEEK_DIR = Path(__file__).resolve().parent
REPO = WEEK_DIR.parents[1]
BUILD = REPO / "build"
BIN = BUILD / "bin"

# name -> command (the input file is appended)
PROGRAMS = {
    "python": [sys.executable, str(WEEK_DIR / "matmul.py")],
    "ijk": [str(BIN / "week1_matmul_ijk")],
    "ikj": [str(BIN / "week1_matmul_ikj")],
}
CPP_TARGETS = {"ijk": "week1_matmul_ijk", "ikj": "week1_matmul_ikj"}

# Last number in the output, e.g. "elapsed: 0.123 s" or a bare "61.2".
NUMBER = re.compile(r"[-+]?\d*\.?\d+(?:[eE][-+]?\d+)?")


def build(targets):
    if not targets:
        return
    cmd = ["cmake", "--build", str(BUILD)]
    for t in targets:
        cmd += ["--target", t]
    print("building:", " ".join(targets))
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"build failed:\n{r.stdout}{r.stderr}")


def run(name, input_file):
    cmd = PROGRAMS[name] + [str(input_file)]
    print(f"running {name} ...", end=" ", flush=True)
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"\n{name} failed (exit {r.returncode}):\n{r.stdout}{r.stderr}")
    numbers = NUMBER.findall(r.stdout)
    if not numbers:
        sys.exit(f"\ncould not find a time in {name}'s output:\n{r.stdout}")
    secs = float(numbers[-1])
    print(f"{secs:.6f} s")
    return secs


def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("input", type=Path, help="matrix file (n, then A, then B)")
    p.add_argument("--only", nargs="+", choices=PROGRAMS, default=list(PROGRAMS),
                   help="which programs to run (default: all)")
    p.add_argument("--csv", type=Path, default=WEEK_DIR / "results" / "runs.csv",
                   help="CSV to append results to")
    args = p.parse_args()

    input_file = args.input.resolve()
    if not input_file.exists():
        sys.exit(f"no such file: {args.input}")
    with open(input_file) as f:
        n = int(f.readline())

    build([CPP_TARGETS[x] for x in args.only if x in CPP_TARGETS])

    when = datetime.datetime.now().isoformat(timespec="seconds")
    rows = [(when, name, input_file.name, n, run(name, input_file))
            for name in args.only]

    args.csv.parent.mkdir(parents=True, exist_ok=True)
    new = not args.csv.exists()
    with open(args.csv, "a", newline="") as f:
        w = csv.writer(f)
        if new:
            w.writerow(["timestamp", "program", "input", "n", "seconds"])
        w.writerows(rows)
    print(f"appended {len(rows)} rows to {args.csv}")


if __name__ == "__main__":
    main()
