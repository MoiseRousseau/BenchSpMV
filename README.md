# Benchmarking SpMV

This is a simple program that evaluation performance of sparse matrix - vector product.
The idea is to identificate the maximum throughput of the system with mulitple concurrent runs.
Maximum throughput is then calculated as the number of floating point multiplication divided by the mean calculation time of the concurrent runs.
Number of floating point multiplication is taken equal to matrix non-zero elements.


## Compilation

Require [Eigen](https://eigen.tuxfamily.org) template library.
Replace the expression `/usr/include/eigen3` below by your path to Eigen

* On x86-64 Unix-like system:

```
c++ -I/usr/include/eigen3 -ftree-vectorize -march=native -funroll-loops -O2 -o bench_x86-64 eigen_bench_main.cpp
```

* On ARM system:
```
c++ -I/usr/include/eigen3 -ftree-vectorize -march=armv8.4-a+simd -funroll-loops -O2 -o bench_armv84 eigen_bench_main.cpp
```

* On Windows, with [MinGW](https://sourceforge.net/projects/mingw/):

```
g++ -I/usr/include/eigen3 -ftree-vectorize -march=native -funroll-loops -O2 -o bench_x86_64_win eigen_bench_main.cpp
```

## Results

Results for matrix ``fcondp2`` from [SuiteSparse](https://sparse.tamu.edu/DNVS/fcondp2).
Optimal concurrent runs is the minimum concurrent runs whose throughput is superior to 95% of the maximum.

| System       | Max. throughput (GFlop/s) | OCR |
|--------------|---------------------------|-----|
| Raspberry Pi 5 |  |  |
| Personal laptop (AMD Ryzen 5500U) | 2.33 | 4 |
| Work laptop (i7 12800H) |  |  |
| Dell workstation (Threadripper X) |  |  |
