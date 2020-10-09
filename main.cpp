#include <iostream>
#include "matrix.hpp"
int main() {
try {
//    int i = 8;
    double arr[] = {1,2,3,4,5,6,7,8,9};
//    double arr2[] = {1,2,3,4,5,6,7,8,9};
    matrix foo(arr, 9);
    matrix bar(3,1);
//
//    cout << "foo\n" << foo;
//    cout << "bar\n" << bar;

    cout << "setting values" << endl;
    bar.set_value(0,0,1);
    bar.set_value(1,0,2);
    bar.set_value(2,0,3);
    cout << "values set" << endl;


    cout << "foo\n" << foo;
    cout << "bar\n" << bar;
    cout << "multiplying...";
    foo *= bar;
    cout << "multiplied" << endl;
    cout << "foo\n" << foo;
} catch (char const* e) {
    cout << (e);
}
    return 0;
}
