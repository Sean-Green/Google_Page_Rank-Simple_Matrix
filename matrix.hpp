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
    matrix(matrix& m) = default;
    matrix(int n);
    matrix(int c, int r);
    matrix(const double vals[], int length);
    void set_value(int c, int r, double val);
    double get_value(int c, int r);
    void clear();
    ~matrix();
    friend ostream& operator<<(ostream& os, matrix&);
    friend bool operator==(matrix& m1, matrix& m2);
    friend bool operator!=(matrix& m1, matrix& m2);
    int get_rows() const{return rows;}
    int get_cols() const{return cols;}

};


#endif //ASSIGNMENT1_MATRIX_HPP
