// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <iostream>
#include <vector>


// You don't have to use the struct. Can help you with MlpNetwork.h
struct mmatrix_dims {
    int rows, cols;
};


class Matrix
{
private:
    int _rows;
    int _cols;
    float** _matrix;

public:
    Matrix(int rows, int cols);
    Matrix();
    Matrix(const Matrix& m);
    ~Matrix();
    int get_rows() const{return _rows;}
    int get_cols() const{return _cols;}
    Matrix& transpose();
    Matrix& vectorize();
    void plain_print() const;
    Matrix dot(const Matrix& m) const;
    float norm() const;
    void swap_rows(int row1, int row2);
    Matrix rref() const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    float sum() const;
    int argmax() const;
    Matrix& operator+=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix& operator=(Matrix m);
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(float c) const;
    friend Matrix operator*(float c, const Matrix& m);
    float& operator[](int k) const;
    float& operator()(int i, int j) const;
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};


#endif //MATRIX_H