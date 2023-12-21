#include <iostream>
#include <string>
#include<cmath>
using namespace std;
unsigned int* compute_squares(unsigned int a[],unsigned int b[],unsigned int n) {
    unsigned int *c;
    c = &b[0];
    for (unsigned int *p = a; *p; ++p) {
        unsigned int curval2 = pow(*p, 2);
        *c = curval2;
        c++;
    }
    return b;
}


int main() {
    unsigned int temparr[5] = {1,6,12,144,55};
    unsigned int temparr2[5] = {1,1,1,1,1};
    unsigned int *p;
    p = compute_squares(temparr,temparr2,5);
    for (int i = 0; i < 5; i++) {
        cout << *(p + i) << endl;
    }
}