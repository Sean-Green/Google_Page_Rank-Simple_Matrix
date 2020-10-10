#pragma clang diagnostic push
#pragma ide diagnostic ignored "VirtualCallInCtorOrDtor"
//
// Created by seanj on 10/8/2020.
//

#include <iostream>
#include "connectivity_matrix.hpp"

connectivity_matrix::connectivity_matrix(double *arr, int length) :matrix(sqrt(length)){
    int i = 0;
    for (int r = 0; r < get_rows(); r++){
        for (int c = 0; c < get_cols(); c++){
            try {
                set_value(r, c, arr[i++]);
            } catch (char const *e) {
                throw "connectivity matrix constructor only takes 1's and 0's";
            }
        }
    }
}

void connectivity_matrix::set_value(int row, int col, double val) {
    if (val != 0 && val != 1) {
        throw "connectivity matrix set_value only takes 1's and 0's";
    }
    matrix::set_value(row, col, val);
}

matrix connectivity_matrix::get_pageRank() {

    matrix left_stochastic(rows);
    matrix teleport(rows);
    double walk_chance= 0.85;
    double tel_chance = (1.0 - walk_chance) * (1.0 / cols);
    teleport.fill(tel_chance);
    for (int col = 0; col < cols; col++) {
        double divisor = 0;
        //get divisor
        for (int row = 0; row < rows; row++) {
            divisor += get_value(row, col);
        }
        if (divisor != 0) {
            for (int row = 0; row < rows; row++) {
                if (get_value(row, col) != 0) {
                    left_stochastic.set_value(row, col, (get_value(row, col) / divisor) * walk_chance);
                }
            }
        } else {
            double value = (1.0 / rows) * walk_chance;
            for (int row = 0; row < rows; row++) {
                    left_stochastic.set_value(row, col, value);
            }
        }
    }

    matrix result = left_stochastic + teleport;
    matrix rank(rows, 1);
    rank.fill(1.0);
    matrix previous_rank;
    do {
        previous_rank = rank;
        rank = result * rank;
    } while (rank != previous_rank);

    double sum = rank.sum();
    for (int row = 0; row < rows; row++){
        rank.set_value(row, 0, (rank.get_value(row,0) / sum));
    }
    return rank;
}

#pragma clang diagnostic pop