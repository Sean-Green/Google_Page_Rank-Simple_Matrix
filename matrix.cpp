//
// Created by seanj on 10/6/2020.
//

#include <iostream>
#include "matrix.hpp"
using namespace std;

matrix::matrix(): rows(1), cols(1) {
    m = new vector<vector<double> > ();
    m->push_back(vector<double>(1,0));
}

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

matrix::matrix(int c, int r) {
    if (r < 1 || c < 1) { throw "rows/cols must be greater than 0"; }
    cols = c;
    rows = r;
    m = new vector<vector<double> > ();
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

void matrix::set_value(int c, int r, double val) {
    if (c >= rows || r >= rows || c < 0 || r < 0) { throw "c/r index out of bounds";}
    (*m)[r][c] = val;
}

double matrix::get_value(int c, int r) {
    if (c >= cols || r >= rows || c < 0 || r < 0) { throw "c/r index out of bounds";}
    return (*m)[r][c];
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

ostream &operator<<(ostream &os, matrix& m) {
    for (int row = 0; row < m.get_rows(); row++){
        for (int col = 0; col < m.get_cols(); col++) {
            os << m.get_value(col,row) << " ";
        }
        os << "\n";
    }
    return os;
}

bool operator==(matrix &m1, matrix &m2) {
    const double TOLERANCE = .001; // first 3 decimals are significant

    int rows = m1.get_rows();
    int cols = m1.get_cols();
    if (rows != m2.get_rows() || cols != m2.get_cols()) {return false;}
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++) {
            // narrowing on purpose
            double v1 = m1.get_value(col, row);
            double v2 = m2.get_value(col, row);
            cout << v1 << " " << v2 << endl;
            if (abs((v1-v2)) < TOLERANCE){
                return false;
            }
        }
    }
    return true;
}

bool operator!=(matrix &m1, matrix &m2) {
    return !(m1==m2);
}



