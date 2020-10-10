#include <iostream>
#include <fstream>
#include <iomanip>
#include "matrix.hpp"
#include "connectivity_matrix.hpp"
#include "rank_matrix.hpp"

int main() {
    //open the file
    ifstream text("../connectivity.txt");
    if (!text) {
        cerr << "File not found!" << endl;
        return 69;
    }
    //store the file in a vector
    double temp;
    vector<double> vect;
    do {
    text >> temp;
    vect.push_back(temp);
    } while (text);
    vect.pop_back();

    // Turns out you can point at a vectors address to get an array.
    double *arr = &vect[0];
    connectivity_matrix m(arr,vect.size());
    rank_matrix r (m);

    cout << "\nConnectivity Matrix:\n" << m;
    cout << "\nPage Rank:\n" << r;
    return 0;

}
