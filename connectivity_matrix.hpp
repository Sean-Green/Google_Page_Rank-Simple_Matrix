//
// Created by seanj on 10/8/2020.
//

#ifndef ASSIGNMENT1_CONNECTIVITY_MATRIX_HPP
#define ASSIGNMENT1_CONNECTIVITY_MATRIX_HPP


#include "matrix.hpp"

class connectivity_matrix : public matrix {

public:
    connectivity_matrix(double arr[], int length);
    void set_value(int row, int col, double val);
    matrix get_pageRank();
};
class rank_matrix: public matrix {
public:
    rank_matrix(connectivity_matrix& cm) {
        if (cm.get_rows() > 0 && cm.get_cols() == 1)
    }
    friend ostream& operator<<(ostream& os, matrix);
};


#endif //ASSIGNMENT1_CONNECTIVITY_MATRIX_HPP
