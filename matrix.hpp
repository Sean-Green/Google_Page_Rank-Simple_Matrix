//
// Created by seanj on 10/6/2020.
//

#ifndef ASSIGNMENT1_MATRIX_HPP
#define ASSIGNMENT1_MATRIX_HPP

#include <vector>
#include <cassert>
#include <cmath>
#include <ostream>

using namespace std;

class matrix {

private:
    vector<vector<double> > * m;
    int rows;
    int cols;

public:
    matrix();
    matrix(int n);
    matrix(const matrix& copymatrix);
    matrix(int c, int r);
    matrix(const double vals[], int length);
    void set_value(int c, int r, double val);
    double& get_value(int c, int r) const;
    void clear();
    ~matrix();
    friend ostream& operator<<(ostream& os, matrix);
    friend bool operator==(matrix& m1, matrix& m2);
    friend bool operator!=(matrix& m1, matrix& m2);
    matrix& operator++();
    matrix operator++(int);
    matrix& operator--();
    matrix operator--(int);
    friend void mySwap(matrix& lhs, matrix& rhs);
    matrix& operator=(matrix m);
    void operator+=(const matrix& m1);
    friend matrix operator+(matrix lhs, const matrix& rhs);
    void operator-=(const matrix& m1);
    friend matrix operator-(matrix lhs, const matrix& rhs);
    void operator*=(matrix& m1);
    friend matrix operator*(matrix lhs, matrix& rhs);
    int get_rows() const{return rows;}
    int get_cols() const{return cols;}
};


#endif //ASSIGNMENT1_MATRIX_HPP
