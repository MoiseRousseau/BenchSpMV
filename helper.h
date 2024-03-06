#ifndef helper_h
#define helper_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include "external/mm.hpp"


typedef MtxReader<int, double, unsigned int> reader_t;
typedef Eigen::Triplet<double> T;
typedef Eigen::SparseMatrix<double, Eigen::ColMajor> SpMat; // declares a column-major sparse

/* 
Generate a random floating point number from -1 to 1
https://stackoverflow.com/questions/33058848/generate-a-random-double-between-1-and-1
*/
double doublerand() 
{
    double div = RAND_MAX / 2.;
    return -1. + (rand() / div);
}

/*
Create a random vector (double format) of size N
*/
void generate_random_vector(Eigen::VectorXd& x, unsigned int N) {
  srand(0);
  x.resize(N);
  for (int i=0; i<N; i++) {
      x[i] = doublerand();
  }
}

/*
Use Matrix-Market to read a mtx matrix and output a Eigen Sparse Matrix
*/
void read_mtx_to_eigen(char* path, SpMat* A)
{
    reader_t reader(path);
    reader_t::coo_type coo = reader.read_coo();
    
    std::cout << "Matrix size (rows,columns): " << coo.num_rows() << "," << coo.num_cols() << std::endl;
    std::cout << "Non zero elements: " << coo.nnz() << std::endl; 
    
    std::vector<T> tripletList;
    for (reader_t::coo_type::entry_type e : coo.entries)
    {
    	tripletList.push_back(T(e.i, e.j, e.e));
    }
    
    A->resize(coo.num_rows(), coo.num_cols());
    A->setFromTriplets(tripletList.begin(), tripletList.end());
}

#endif
