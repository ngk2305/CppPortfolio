#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

template <typename T>     
class Matrix {
public:
    Matrix(int r, int c) : r_(r), c_(c), data_(r*c,0) {}


    T& operator()(int i, int j) {   // makes  line(x)  work
        return data_[i*c_+j];
    }

    T operator()(int i, int j) const {   // makes  line(x)  work
        return data_[i*c_+j];
    }

    int r() const { return r_;}
    int c() const { return c_;}


private:
    int r_;
    int c_;
    std::vector<T> data_;
};

template <typename T>  
Matrix<T> load_matrix(std::ifstream& f, int r, int c){

    Matrix<T> A(r,c);
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
           f >> A(i,j) ;
        }
    }
    return A;
}

template <typename T>
Matrix<T> matmul_ijk(const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.c() == B.r());
    Matrix<T> C( A.r(), B.c() ); 
    for (int i = 0; i < A.r(); ++i)
        for (int j = 0; j < B.c(); ++j)
            for (int k = 0; k < A.c(); ++k)
                C(i,j) += A(i,k) * B(k,j);
    return C;
}

template <typename T>
Matrix<T> matmul_ikj(const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.c() == B.r());
    Matrix<T> C( A.r(), B.c() ); 
    for (int i = 0; i < A.r(); ++i)
        for (int k = 0; k < A.c(); ++k)
            for (int j = 0; j < B.c(); ++j)
                C(i,j) += A(i,k) * B(k,j);
    return C;
}