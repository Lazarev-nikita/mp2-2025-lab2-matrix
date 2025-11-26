#include "gtest/gtest.h"
#include "utmatrix.h"

TEST(TMatrix, can_create_matrix_with_positive_size) {
    EXPECT_NO_THROW(TMatrix<int> m(4));
}

TEST(TMatrix, throws_when_create_with_negative_size) {
    EXPECT_THROW(TMatrix<int> m(-1), std::invalid_argument);
}

TEST(TMatrix, can_copy_matrix) {
    TMatrix<int> m1(3);

    m1[0][0]=1; m1[0][1]=2; m1[0][2]=3;
    m1[1][1]=4; m1[1][2]=5;
    m1[2][2]=6;

    TMatrix<int> m2(m1);

    EXPECT_EQ(m1, m2);
}

TEST(TMatrix, addition_and_subtraction) {
    TMatrix<int> a(3), b(3);

    for(int i=0;i<3;i++)
        for(int j=i;j<3;j++) {
            a[i][j]=i+j;
            b[i][j]=1;
        }

    auto c = a + b;
    auto d = a - b;

    EXPECT_EQ(c[0][2], a[0][2] + 1);
    EXPECT_EQ(d[2][2], a[2][2] - 1);
}
