# CppPortfolio

My C++ learning log on the road to GPU programming.

## Layout

| Path | What |
|------|------|
| `phase0/week1` … `week4` | Weekly exercises (each `.cpp` builds to its own program) |
| `common/` | Shared header-only helpers (e.g. `timer.hpp`) |

## Build & run

```bash
cmake -S . -B build -G Ninja      # configure (Release by default)
cmake --build build               # build everything
./build/bin/week1_hello           # programs are named <week>_<file>
```

In VS Code: open a `.cpp` and press **F5** to build it in Debug and step through it with gdb.

## Results

| Kernel / program | My result | Reference result | % of peak | Notes |
|------------------|-----------|------------------|-----------|-------|
|                  |           |                  |           |       |
