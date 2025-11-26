#include "gtest/gtest.h"
#include "utmatrix.h"

TEST(TVector, can_create_vector_with_positive_length) {
    EXPECT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, throws_when_create_with_negative_length) {
    EXPECT_THROW(TVector<int> v(-1), std::invalid_argument);
}

TEST(TVector, can_copy_vector) {
    TVector<int> v1(3);
    v1[0]=1; v1[1]=2; v1[2]=3;

    TVector<int> v2(v1);
    EXPECT_EQ(v1, v2);
}

TEST(TVector, can_assign_vector) {
    TVector<int> v1(3);
    v1[0]=5; v1[1]=6; v1[2]=7;

    TVector<int> v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(TVector, addition_and_subtraction_works) {
    TVector<int> a(3);
    TVector<int> b(3);

    for (int i=0;i<3;i++) { a[i]=i; b[i]=2*i; }

    auto c = a + b;
    auto d = b - a;

    EXPECT_EQ(c[1], 1 + 2);
    EXPECT_EQ(d[2], 4 - 2);
}

TEST(TVector, vectors_with_different_start_index_not_equal) {
    TVector<int> a(3,1);
    TVector<int> b(3,0);
    EXPECT_NE(a, b);
}
