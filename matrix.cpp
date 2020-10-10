//
// Created by seanj on 10/6/2020.
//

#include <iostream>
#include "matrix.hpp"
#include "connectivity_matrix.hpp"


// Called in operator ==
// For a tolerance of .001.
// Rounding errors were allowing things outside of tolerance to return true.
const double TOLERANCE = .0009;
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                              Constructors                                                      ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Default Matrix, contains 1 row and 1 column of 0.0
matrix::matrix(): rows(1), cols(1) {
    m = new vector<vector<double> > ();
    m->push_back(vector<double>(1,0));
}

// Square matrix, takes an int n > 0 and returns an empty nxn matrix
matrix::matrix(const int n) {
    // NEEDS ASSERT n > 0
    if (n < 1) { throw "n must be greater than 0";}
    rows = n;
    cols = n;
    m = new vector<vector<double> > ();
    for (int row = 0; row < n; row++) {
        m->push_back(vector<double>(cols, 0));
    }
}

// Copy constructor, takes a reference to another matrix and created a duplicate
matrix::matrix(const matrix &copymatrix):matrix(copymatrix.rows, copymatrix.cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] = copymatrix.get_value(row, col);
        }
    }
}

// Variable size empty matrix constructor matrix, takes int c, int r and returns a c x r size matrix
matrix::matrix(const int row_num, const int col_num){
    if (row_num < 1 || col_num < 1) { throw "rows/cols must be greater than 0"; }
    m = new vector<vector<double> > ();
    rows = row_num;
    cols = col_num;
    for (int row = 0; row < rows; row++) {
            m->push_back(vector<double>(cols, 0));
    }
}

// Creates a matrix from an array, row by row, provided the array is a square number of values
matrix::matrix(const double vals[], const int length):matrix(sqrt(length)) {
    double n = sqrt(length);
    if (n - (int)sqrt(length) > 0) { throw "array length not an integer square";}
    int i = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] = vals[i++];
        }
    }
}

// Sets a value within the matrix
void matrix::set_value(const int row, const int col, const double val) {
    if (col >= cols || row >= rows || col < 0 || row < 0) { throw "c/r index out of bounds";}
    (*m)[row][col] = val;
}

// Gets a value from the matrix
double& matrix::get_value(const int row, const int col) const {
    if (col >= cols || row >= rows || col < 0 || row < 0) { throw "c/r index out of bounds";}
    return (*m)[row][col];
}

// resets a matrix to complete zero
void matrix::clear() {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] = 0;
        }
    }
}

// Destructor deallocates the vector with our values.
matrix::~matrix() {
    delete m;
}

// Insertion operator for printing to console
ostream &operator<<(ostream &os, matrix m) {
    for (int row = 0; row < m.get_rows(); row++){
        for (int col = 0; col < m.get_cols(); col++) {
            os << m.get_value(row,col) << " ";
        }
        os << "\n";
    }
    return os;
}

// Boolean operator compare 2 matrices within a certain tolerance as defined above
bool operator==(matrix &m1, matrix &m2) {
    int rows = m1.get_rows();
    int cols = m1.get_cols();
    if (rows != m2.get_rows() || cols != m2.get_cols()) {return false;}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            double v1 = m1.get_value(row, col);
            double v2 = m2.get_value(row, col);
            if (abs((v1-v2)) >= TOLERANCE){
                return false;
            }
        }
    }
    return true;
}

// comparison operator
bool operator!=(matrix &m1, matrix &m2) {
    return !(m1==m2);
}

// PREFIX: increments every value in a matrix by 1.0, then returns the matrix
matrix &matrix::operator++() {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] += 1.0;
        }
    }
    return *this ;
}

// POSTFIX: increments the matrix with the prefix operator, but returns the value before incrementation
matrix matrix::operator++(int) {
    matrix temp(*this);
    operator++();
    return temp;
}

// PREFIX: decrements every value in a matrix by 1.0, then returns the matrix, cannot decrease below 0.
matrix &matrix::operator--() {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] -= 1.0;
            if ((*m)[row][col] < 0) {(*m)[row][col]=0;}
        }
    }
    return *this ;
}

// POSTFIX: decrements the matrix with the prefix operator, but returns the value before decrementation
matrix matrix::operator--(int) {
    matrix temp(*this);
    operator--();
    return temp;
}

// swaps all the values between two matrices
void mySwap(matrix& lhs, matrix& rhs){
    using std::swap;
    swap(lhs.rows, rhs.rows);
    swap(lhs.cols, rhs.cols);
    swap(lhs.m, rhs.m);
}

// uses the = operator to copy and swap values
matrix &matrix::operator=(matrix m) {
    mySwap(*this, m);
    return *this;
}

// adds another matrices values to this one
void matrix::operator+=(const matrix& m1) {
    if (rows != m1.get_rows() || cols != m1.get_cols()){ throw "Matrices are different sizes";}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] += m1.get_value(row, col);
        }
    }
}

// adds two matrices together and returns the result
matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs;
    return lhs;
}

// Subtracts a matrix from this one and returns the result
void matrix::operator-=(const matrix &m1) {
    if (rows != m1.get_rows() || cols != m1.get_cols()){ throw "Matrices are different sizes";}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] -= m1.get_value(row, col);
            if ((*m)[row][col] < 0) {(*m)[row][col] = 0;}
        }
    }
}

// Subtracts 2 matrices and returns the results
matrix operator-(matrix lhs, const matrix &rhs) {
    lhs -= rhs;
    return lhs;
}

// Performs matrix multiplication with this matrix and another, stores the result in this matrix with the swap method.
void matrix::operator*=(matrix &m1) {
    if (cols != m1.get_rows()) { throw "first matrix' cols don't match second matrix' rows";}
    auto *m2 = new vector<vector<double> >();
    for (int row = 0; row < rows; row++) {
        m2->push_back(vector<double>(m1.get_cols(), 0));
    }
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < m1.get_cols(); col++) {
            double value(0.0);
                for (int i = 0; i < rows; i++) {
                value += (*m)[row][i] * m1.get_value(i, col);
            }
            (*m2)[row][col] = value;
        }
    }
    swap(m,m2);
    cols = m1.get_cols();
    delete m2;
}

// multiplies 2 matrices and returns the result
matrix operator*(matrix lhs, matrix &rhs) {
    lhs *= rhs;
    return lhs;
}

// fills this matrix with the given value
void matrix::fill(const double val) {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] = val;
        }
    }
}

// adds all the values in the matrix and returns the total
double matrix::sum() {
    double sum = 0;
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            sum += (*m)[row][col];
        }
    }
    return sum;
}







