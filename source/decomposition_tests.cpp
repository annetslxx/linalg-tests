#include <gtest/gtest.h>
#include <matrix.h>

TEST(DecompositionTest, LUDecomposition) {
    linalg::Matrix A = {{2, 3, 1, 5}, {6, 13, 5, 19}, {2, 19, 10, 23}, {4, 10, 11, 31}};
    auto [L, U] = A.lu_decompose();

    linalg::Matrix L_expected = {{1, 0, 0, 0}, {3, 1, 0, 0}, {1, 4, 1, 0}, {2, 1, 7, 1}};
    linalg::Matrix U_expected = {{2, 3, 1, 5}, {0, 4, 2, 4}, {0, 0, 1, 2}, {0, 0, 0, 3}};

    ASSERT_EQ(L, L_expected);
    ASSERT_EQ(U, U_expected);

    linalg::Matrix A_reconstructed = L * U;
    ASSERT_EQ(A, A_reconstructed);
}
