#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Matrix.h"
#define MINIMUM_BLUR 0.1


Matrix::Matrix(int rows, int cols)
{
    _cols = cols;
    _rows = rows;
    _matrix = new float*[_rows]();
    for (int i = 0; i<_rows; ++i)
    {
        _matrix[i] = new float[_cols]();
    }
}
Matrix::Matrix(): Matrix(1,1){}
Matrix::Matrix(const Matrix& m): _rows(m._rows), _cols(m._cols) {
    _matrix = new float*[_rows];
    for (int i = 0; i<_rows; i++)
    {
        _matrix[i] = new float[_cols]();
    }
    for(int i = 0; i<_rows; i++) {
        for(int j = 0; j<_cols; j++) {
            _matrix[i][j] = m._matrix[i][j];
        }
    }
}
Matrix::~Matrix()
{
    for (int i = 0; i < _rows; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}


Matrix& Matrix::transpose() {

    Matrix newmatrix(_cols, _rows);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            newmatrix._matrix[j][i] = _matrix[i][j];
        }
    }
    std::swap(_matrix, newmatrix._matrix);
    std::swap(_rows, _cols);
    return *this;
}

Matrix& Matrix::vectorize() {
    Matrix w_vector(_rows * _cols, 1);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            w_vector(i * _cols + j, 0) = _matrix[i][j];
        }
    }
    std::swap(_matrix, w_vector._matrix);
    std::swap(_cols, w_vector._cols);
    std::swap(_rows, w_vector._rows);
    return *this;
}


void Matrix::plain_print() const {
    for(int i = 0; i<_rows; i++) {
        for(int j=0; j<_cols; j++) {
            std::cout<< _matrix[i][j] <<" ";
        }
        std::cout<<"\n";
    }
}

Matrix Matrix::dot(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols) {
        throw std::invalid_argument("Matrix dimensions must"
                                    " match for dotting.");}
    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result._matrix[i][j] = _matrix[i][j] * m._matrix[i][j];
        }
    }
    return result;
}

float Matrix::norm() const {
    float sum_of_squares = 0.0;
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            sum_of_squares += _matrix[i][j] * _matrix[i][j];
        }
    }
    return std::sqrt(sum_of_squares);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
    for(int i = 0; i<m._rows; i++) {
        for(int j=0; j<m._cols; j++) {
            if(m._matrix[i][j] > MINIMUM_BLUR) {
                os << "**";}
            else{os << "  ";
            }
        }
        os << "\n";
    }
    return os;
}


float Matrix::sum() const
{
    float sum = 0;
    for(int i = 0; i<_rows; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            sum += _matrix[i][j];
        }
    }
    return sum;
}

int Matrix::argmax() const
{
    if (_rows == 0 || _cols == 0) {
        throw std::runtime_error("Matrix is empty.");
    }
    int saved_index = 0;
    float num = _matrix[0][0];
    int cur_index = 0;
    for(int i = 0; i<_rows; i++)
    {
        for(int j=0; j<_cols; j++)
        {
            if (_matrix[i][j] > num)
            {
                saved_index = cur_index;
                num = _matrix[i][j];
            }
            cur_index ++;
        }
    }
    return saved_index;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    if (_rows != m._rows || _cols != m._cols) {
        throw std::invalid_argument("Matrix dimensions "
                                    "must match for addition.");
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] += m._matrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const
{
    if (_rows != m._rows || _cols != m._cols) {
        throw std::invalid_argument("Matrix dimensions"
                                    " must match for addition.");
    }
    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result._matrix[i][j] = _matrix[i][j] + m._matrix[i][j];
        }
    }
    return result;
}


Matrix& Matrix::operator=(Matrix m)
{
    std::swap(_cols,m._cols);
    std::swap(_rows,m._rows);
    std::swap(_matrix,m._matrix);
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (_cols != other._rows) {
        throw std::invalid_argument("Matrix dimensions "
                                    "do not match for multiplication");
    }
    Matrix result(_rows, other._cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < other._cols; ++j) {
            for (int k = 0; k < _cols; ++k) {
                result._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    return result;
}


Matrix Matrix::operator*(float c) const {
    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result._matrix[i][j] = _matrix[i][j] * c;
        }
    }
    return result;
}

Matrix operator*(float c, const Matrix& m) {
    return m * c;}



void Matrix::swap_rows(int row1, int row2)
{
    if (row1 != row2)
    {
        float* temp = _matrix[row1];
        _matrix[row1] = _matrix[row2];
        _matrix[row2] = temp;
    }
}

Matrix Matrix::rref() const
{
    Matrix result(*this);
    int lead = 0;
    for (int r = 0; r < result._rows; r++){
        if (lead >= result._cols) {
            return result;
        }
        int i = r;
        while (result._matrix[i][lead] == 0){
            i++;
            if (i == result._rows){
                i = r;
                lead++;
                if (lead == result._cols) {
                    return result;
                }
            }
        }
        result.swap_rows(i, r);
        float lv = result._matrix[r][lead];
        for (int j = 0; j < result._cols; j++) {
            result._matrix[r][j] /= lv;
        }
        for (int i = 0; i < result._rows; i++){
            if (i != r){
                lv = result._matrix[i][lead];
                for (int j = 0; j < result._cols; j++) {
                    result._matrix[i][j] -= lv * result._matrix[r][j];
                }
            }
        }
        lead++;
    }
    return result;
}

float &Matrix::operator()(int i, int j) const {
     if (i < 0 || i >= _rows || j < 0 || j >= _cols) {
         throw std::out_of_range("Matrix indices are"
                                 " out of bounds");
    }
    return _matrix[i][j];
}


float& Matrix::operator[](int k) const {
    if (k < 0 || k >= _cols * _rows) {
        throw std::out_of_range("k must be in the range "
                                "0 <= k < cols * rows");
    }
    // Calculate row and column indices
    int row_index = k / _cols;
    int col_index = k % _cols;
    return _matrix[row_index][col_index];
}




std::istream& operator>>(std::istream& is, Matrix& m) {
    size_t expected_size = m._rows * m._cols * sizeof(float);
    std::ifstream* ifs = dynamic_cast<std::ifstream*>(&is);
    if (ifs) {
        ifs->seekg(0, std::ios::end);
        size_t file_size = ifs->tellg();
        ifs->seekg(0, std::ios::beg);

        if (file_size < expected_size) {
            throw std::runtime_error("Input stream does"
                                     " not have enough data"
                                     " to fill the matrix.");
        }
    }

    // Read data into the matrix
    for (int i = 0; i < m._rows; ++i) {
        is.read(reinterpret_cast<char*>(m._matrix[i]),
            m._cols * sizeof(float));
        if (!is) {
            throw std::runtime_error("Error reading matrix data.");
        }
    }

    return is;
}