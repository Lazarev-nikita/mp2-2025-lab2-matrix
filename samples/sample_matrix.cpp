#include <iostream>
#include "utmatrix.h"

int main() {
    std::cout << "Sample matrix operations\n";

    TMatrix<int> A(3), B(3);

    A[0][0]=1; A[0][1]=2; A[0][2]=3;
    A[1][1]=4; A[1][2]=5;
    A[2][2]=6;

    B[0][0]=10; B[0][1]=20; B[0][2]=30;
    B[1][1]=40; B[1][2]=50;
    B[2][2]=60;

    auto C = A + B;

    std::cout << "C[0][2] = " << C[0][2] << "\n";

    auto D = C - A;

    std::cout << "D[1][2] = " << D[1][2] << "\n";

    return 0;
}
