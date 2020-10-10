//
// Created by seanj on 10/9/2020.
//

#include <iomanip>
#include "rank_matrix.hpp"

// special insertion operator for rank matrix
ostream& operator<<(ostream& os, rank_matrix m) {
    os << fixed;
    os << setprecision(2);
    char page = 'A';
    for (int row = 0; row < m.get_rows(); row++){
        for (int col = 0; col < m.get_cols(); col++) {
            os <<"Page " << page++ << ": " << (m.get_value(row,col) * 100) << "%";
        }
        os << "\n";
    }
    return os;
}