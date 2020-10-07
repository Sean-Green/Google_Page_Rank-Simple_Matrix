#include <iostream>
#include "matrix.hpp"

int main() {
try {
    matrix m(2);
    matrix n(5, 6);
    std::cout << m << n;
    double arr[] = {1.0, 2.0, 3.0001, 4.0};
    double arr2[] = {1.0, 2.0, 3.0, 4.0};
    matrix foo(arr, 4);
    matrix bar(arr2, 4);
    cout << foo;
//    foo.clear();
    cout << "foo\n" << foo;
//    foo.set_value(1,1,1);
    cout << "bar\n" << bar;
    cout << "foo\n" << foo;

    if (bar == foo) {
        cout << "foo bar match";
    } else {
        cout << "foo bar nono";
    }
} catch (char const* e) {
    cout << (e);
}
    return 0;
}
