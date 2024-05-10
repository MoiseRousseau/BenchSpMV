#include <Eigen/Sparse>
#include <Eigen/Core>
#include <chrono>
#include <iostream>
#include "helper.h"

typedef Eigen::SparseMatrix<double, Eigen::RowMajor> SpMat; // declares a column-major sparse matrix type of double


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "Benchmark SpMV multiplication time using Eigen" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " [matrix_file] [repeat]" << std::endl;
        exit(1);
    }
    
    int repeat = atoi(argv[2]);
    
    std::cout << "Loading matrix:" << std::endl;
    SpMat inA;
    read_mtx_to_eigen(argv[1], &inA);
    
    Eigen::VectorXd x(inA.outerSize());
    for (unsigned int i=0; i < x.size(); i++) x[i] = 1.;
    Eigen::VectorXd y(inA.innerSize());
    
    std::cout << "Perform SpMV:" << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i=0; i<repeat; i++) {
    	y = inA * x;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Eigen time: " << (t2-t1).count()/1e9 << " s"<< std::endl;
    
    double norm = 0.;
    for (double v : y) norm += v*v;
    std::cout << "Y squared 2-norm: " << norm << std::endl;
    std::cout << "GFLOP/s: " << (double) (inA.nonZeros() * repeat) / (t2-t1).count() << std::endl;
    
    
    return 0;
}
 
