//
// Created by seanj on 10/9/2020.
//

#ifndef ASSIGNMENT1_RANK_MATRIX_HPP
#define ASSIGNMENT1_RANK_MATRIX_HPP


#include "matrix.hpp"
#include "connectivity_matrix.hpp"

class rank_matrix: public matrix {
public:

    // constructor takes a connectivity matrix and uses its get_pagerank function to to get a matrix which we then copy.
    rank_matrix(connectivity_matrix m):matrix(m.get_page_rank()){
        if (get_rows() < 1 || get_cols() != 1) {throw "rank matrix must be of size nx1 where n > 0";}
    };
    friend ostream& operator<<(ostream& os, rank_matrix m);
};



#endif //ASSIGNMENT1_RANK_MATRIX_HPP
