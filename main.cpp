#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "connectivity_matrix.hpp"

int main() {
    ifstream text("../connectivity.txt");
    if (text) {
        cout << "fileread!" << endl;
    }
    double temp;
    vector<double> vect;
    do {
    text >> temp;
    cout << temp << endl;
    vect.push_back(temp);
    } while (text);
    vect.pop_back();
    cout << vect.size() << endl;
    // Turns out you can point at a vectors address to get an array.
    double *arr = &vect[0];
    connectivity_matrix m(arr,vect.size());
    cout << "Connectivity Matrix:\n" << m;
    cout << "Rank:\n" << m.get_pageRank();
    return 0;

}
