#include <iostream>
#include "tmatrix.h"

int main()
{
    using std::cout;
    using std::endl;

    TDynamicMatrix<int> A(4), B(4);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            A[i][j] = i + j;
            B[i][j] = (i == j) ? 1 : 0;
        }
    }

    TDynamicMatrix<int> C = A;
    cout << "C == A ? " << (C == A) << endl;

    TDynamicMatrix<int> D = A + B;
    cout << "D[2][3] = " << D[2][3] << endl;

    TDynamicMatrix<int> E = D - A;
    cout << "E[1][1] = " << E[1][1] << endl;

    TDynamicVector<int> v(4);
    for (int i = 0; i < 4; ++i) v[i] = i + 1;
    TDynamicVector<int> r = A * v;
    cout << "A * v =";
    for (size_t i = 0; i < r.size(); ++i) cout << ' ' << r[static_cast<int>(i)];
    cout << endl;

    return 0;
}
