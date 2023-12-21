#include "Matrix.h"
int main() {
    Matrix m1(3,4,5);
    Matrix m2(4,3,2);


    m1.set(0,0,4);
    m1.set(2,2,2);
    double val;
    m1.get(2,2,val);
    m1.multiply_by_coefficient(3);
    m1.transpose();


    m1.add(m2);

    std:: cout << m1;
}