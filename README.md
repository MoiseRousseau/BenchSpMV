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
c++ -I/usr/include/eigen3 -ftree-vectorize -march=native -funroll-loops -O2 -fopenmp -o bench_x86-64 eigen_bench_main.cpp
```

* On ARM system:
```
c++ -I/usr/include/eigen3 -ftree-vectorize -march=armv8.4-a+simd -funroll-loops -O2 -fopenmp -o bench_armv84 eigen_bench_main.cpp
```

* On Windows, with [MinGW](https://sourceforge.net/projects/mingw/):

```
g++ -I/usr/include/eigen3 -ftree-vectorize -march=native -funroll-loops -O2 -fopenmp -o bench_x86_64_win eigen_bench_main.cpp
```

## Results

Results for matrix ``fcondp2`` from [SuiteSparse](https://sparse.tamu.edu/DNVS/fcondp2) (single thread per run).
Optimal concurrent runs is the minimum concurrent runs whose throughput is superior to 95% of the maximum.

| System       | Max. throughput (GFLOP/s) | OCR | CAD/GFLOP/s |
|--------------|---------------------------|-----|-------------|
| Raspberry Pi 5 | 0.76 | 1 | 130 |
| Laptop Ryzen 5500U - 24GB DDR4 | 2.33 | 4 | 270 | 
| Laptop i7 12800H - 2x16GB DDR5-4800 | 4.5 | 6 | 500 |
| Workstation Threadripper 5955WX - 8x16GB DDR4-3200 | 6.9 | 6 | 400 |
| Server E5-2650v4 - 8x16GB DDR4-2400 | 4.8 | 10 | 200 |
| Server EPYC 9274F - 16x816GB DDR5-4800 | 34 | 24 | 500 |
