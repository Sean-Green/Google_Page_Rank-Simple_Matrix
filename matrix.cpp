//
// Created by seanj on 10/6/2020.
//

#include <iostream>
#include "matrix.hpp"
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
matrix::matrix(int n) {
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
matrix::matrix(int row_num, int col_num){
    if (row_num < 1 || col_num < 1) { throw "rows/cols must be greater than 0"; }
    m = new vector<vector<double> > ();
    rows = row_num;
    cols = col_num;
    for (int row = 0; row < rows; row++) {
            m->push_back(vector<double>(cols, 0));
    }
}


matrix::matrix(const double vals[], int length):matrix(sqrt(length)) {
    double n = sqrt(length);
    if (n - (int)sqrt(length) > 0) { throw "array length not an integer square";}
    int i = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] = vals[i++];
        }
    }
}

void matrix::set_value(int row, int col, double val) {
    if (col >= cols || row >= rows || col < 0 || row < 0) { throw "c/r index out of bounds";}
    (*m)[row][col] = val;
}

double& matrix::get_value(int row, int col) const {
    if (col >= cols || row >= rows || col < 0 || row < 0) { throw "c/r index out of bounds";}
    return (*m)[row][col];
}

void matrix::clear() {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] = 0;
        }
    }
}

matrix::~matrix() {
    delete m;
}

ostream &operator<<(ostream &os, matrix m) {
    for (int row = 0; row < m.get_rows(); row++){
        for (int col = 0; col < m.get_cols(); col++) {
//            cout << m.get_value(row, col);
            os << m.get_value(row,col) << " ";
        }
        os << "\n";
    }
    return os;
}

bool operator==(matrix &m1, matrix &m2) {
    // first 3 decimals are significant, rounding errors in doubles are making .001 int .0009
    const double TOLERANCE = .0009;
    int rows = m1.get_rows();
    int cols = m1.get_cols();

    if (rows != m2.get_rows() || cols != m2.get_cols()) {return false;}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            double v1 = m1.get_value(row, col);
            double v2 = m2.get_value(row, col);
            // Doesn't work, returns 3.009999999 instead of the 3.001 that actually exists
            if (abs((v1-v2)) >= TOLERANCE){
                return false;
            }
        }
    }
    return true;
}

bool operator!=(matrix &m1, matrix &m2) {
    return !(m1==m2);
}

matrix &matrix::operator++() {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] += 1.0;
        }
    }
    return *this ;
}

matrix matrix::operator++(int) {
    matrix temp(*this);
    operator++();
    return temp;
}

matrix &matrix::operator--() {
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] -= 1.0;
            if ((*m)[row][col] < 0) {(*m)[row][col]=0;}
        }
    }
    return *this ;
}

matrix matrix::operator--(int) {
    matrix temp(*this);
    operator--();
    return temp;
}

void mySwap(matrix& lhs, matrix& rhs){
    using std::swap;
    swap(lhs.rows, rhs.rows);
    swap(lhs.cols, rhs.cols);
    swap(lhs.m, rhs.m);
}

matrix &matrix::operator=(matrix m) {
    mySwap(*this, m);
    return *this;
}

void matrix::operator+=(const matrix& m1) {
    if (rows != m1.get_rows() || cols != m1.get_cols()){ throw "Matrices are different sizes";}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] += m1.get_value(row, col);
        }
    }
}

matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs;
    return lhs;
}

void matrix::operator-=(const matrix &m1) {
    if (rows != m1.get_rows() || cols != m1.get_cols()){ throw "Matrices are different sizes";}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            (*m)[row][col] -= m1.get_value(row, col);
            if ((*m)[row][col] < 0) {(*m)[row][col] = 0;}
        }
    }
}

matrix operator-(matrix lhs, const matrix &rhs) {
    lhs -= rhs;
    return lhs;
}

// Multiply the rows in the first matrix, and multiply it by the columns in the second


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

matrix operator*(matrix lhs, matrix &rhs) {
    lhs *= rhs;
    return lhs;
}







