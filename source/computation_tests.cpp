//
// Created by Anna on 18.10.25.
//

#include <gtest/gtest.h>
#include <matrix.h>

using namespace linalg;

TEST(MatrixTest, TraceBasic) {
  Matrix m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

  EXPECT_NEAR(m.trace(), 15.0, 1e-9); // 1 + 5 + 9 = 15
}

TEST(MatrixTest, TraceSingleElement) {
  Matrix m = {42.0};

  EXPECT_NEAR(m.trace(), 42.0, 1e-9);
}

TEST(MatrixTest, NormVector) {
  Matrix m{{3.0, 4.0}};

  EXPECT_NEAR(m.norm(), 5.0, 1e-9); // sqrt(3^2 + 4^2) = 5
}

TEST(MatrixTest, NormMatrix) {
  Matrix m{{1.0, 2.0}, {3.0, 4.0}};

  // sqrt(1^2 + 2^2 + 3^2 + 4^2) = sqrt(30)
  EXPECT_NEAR(m.norm(), std::sqrt(30.0), 1e-9);
}

TEST(MatrixTest, NormZero) {
  Matrix m{{0.0, 0.0}, {0.0, 0.0}};

  EXPECT_NEAR(m.norm(), 0.0, 1e-9);
}

TEST(MatrixTest, DetBasic) {
  Matrix m{{1.0, 2.0}, {3.0, 4.0}};

  EXPECT_NEAR(m.det(), -2.0, 1e-9); // 1*4 - 2*3 = -2
}

TEST(MatrixTest, DetThreeByThree) {
  Matrix m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 10.0}};

  EXPECT_NEAR(m.det(), -3.0, 1e-9);
}

TEST(MatrixTest, DetIdentity) {
  Matrix m = create_identity_matrix(3);

  EXPECT_NEAR(m.det(), 1.0, 1e-9);
}

TEST(MatrixTest, ConcatenateHorizontal) {
  Matrix A{{1.0, 2.0}, {3.0, 4.0}};
  Matrix B{{5.0, 6.0}, {7.0, 8.0}};

  Matrix result = concatenate(A, B);
  Matrix expected{{1.0, 2.0, 5.0, 6.0}, {3.0, 4.0, 7.0, 8.0}};

  EXPECT_TRUE(result == expected);
}

TEST(MatrixTest, ConcatenateDifferentColumns) {
  Matrix A{{1.0, 2.0}, {3.0, 4.0}};
  Matrix B = {5.0, 6.0};

  Matrix result = concatenate(A, B);
  Matrix expected{{1.0, 2.0, 5.0}, {3.0, 4.0, 6.0}};

  EXPECT_TRUE(result == expected);
}

TEST(MatrixTest, RankFull) {
  Matrix m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 10.0}};

  EXPECT_EQ(m.rank(), 3);
}

TEST(MatrixTest, RankDeficient) {
  Matrix m{{1.0, 2.0, 3.0},
           {2.0, 4.0, 6.0}, // 2 * первая строка
           {4.0, 5.0, 6.0}};

  EXPECT_EQ(m.rank(), 2); // Только 2 независимые строки
}

TEST(MatrixTest, RankZero) {
  Matrix m{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

  EXPECT_EQ(m.rank(), 0);
}

TEST(MatrixTest, RankOne) {
  Matrix m{{1.0, 2.0, 3.0},
           {2.0, 4.0, 6.0},  // 2 * первая строка
           {3.0, 6.0, 9.0}}; // 3 * первая строка

  EXPECT_EQ(m.rank(), 1); // Все строки пропорциональны
}

TEST(MatrixTest, TraceNonSquareThrows) {
  Matrix m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};

  EXPECT_THROW(m.trace(), std::runtime_error);
}

TEST(MatrixTest, DetNonSquareThrows) {
  Matrix m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};

  EXPECT_THROW(m.det(), std::runtime_error);
}

TEST(MatrixTest, ConcatenateDifferentRowsThrows) {
  Matrix A{{1.0, 2.0}, {3.0, 4.0}};
  Matrix B{{5.0, 6.0}}; // Разное количество строк

  EXPECT_THROW(concatenate(A, B), std::runtime_error);
}

TEST(MatrixTest, NegativeDet) {
  Matrix m{{-1, -2}, {-3, -4}};

  EXPECT_NEAR(m.det(), -2.0, 1e-9);
}

TEST(MatrixTest, PowerZero) {
  // A^0 = E
  Matrix A = {{1.0, 2.0}, {3.0, 4.0}};
  Matrix A0 = power(A, 0);
  Matrix E = create_identity_matrix(2);

  EXPECT_TRUE(A0 == E);
}

TEST(MatrixTest, PowerPositive) {
  Matrix A = {{2.0, 0.0}, {0.0, 3.0}};
  Matrix A3 = power(A, 3);

  // [2 0]^3 = [8  0]
  // [0 3]     [0 27]

  EXPECT_NEAR(A3(0, 0), 8.0, 1e-9);
  EXPECT_NEAR(A3(1, 1), 27.0, 1e-9);
}

TEST(MatrixTest, PowerNegative) {
  Matrix A = {{2.0, 0.0}, {0.0, 3.0}};
  Matrix A_minus1 = power(A, -1);

  // [2 0]^(-1) = [0.5   0  ]
  // [0 3]        [0   0.333]

  EXPECT_NEAR(A_minus1(0, 0), 0.5, 1e-9);
  EXPECT_NEAR(A_minus1(1, 1), 1.0 / 3.0, 1e-9);
}

TEST(MatrixTest, TransposeInverse) {
  // (A^T)^(-1) = (A^(-1))^T
  Matrix A = {{4.0, 7.0}, {2.0, 6.0}};

  Matrix AT = transpose(A);
  Matrix AT_inv = invert(AT);

  Matrix A_inv = invert(A);
  Matrix A_inv_T = transpose(A_inv);

  EXPECT_TRUE(AT_inv == A_inv_T);
}

TEST(MatrixTest, ProductInverse) {
  // (A1 * A2)^(-1) = A2^(-1) * A1^(-1)
  Matrix A1 = {{1.0, 2.0}, {3.0, 4.0}};
  Matrix A2 = {{2.0, 1.0}, {1.0, 3.0}};

  Matrix product = A1 * A2;
  Matrix product_inv = invert(product);

  Matrix A2_inv = invert(A2);
  Matrix A1_inv = invert(A1);
  Matrix expected = A2_inv * A1_inv;

  EXPECT_TRUE(product_inv == expected);
}

TEST(MatrixTest, PowerOfInverse) {
  // (A^(-1))^6 = (A^(-2))^3
  Matrix A = {{2.0, 0.0}, {0.0, 3.0}};

  Matrix A_inv = invert(A);
  Matrix left = power(A_inv, 6);

  Matrix A_minus2 = power(A, -2);
  Matrix right = power(A_minus2, 3);

  EXPECT_TRUE(left == right);
}

TEST(MatrixTest, SolvesSimple2x2System) {
  Matrix A = {{2.0, 1.0}, {1.0, 3.0}};
  Matrix f = {3.0, 4.0};

  Matrix x = solve(A, f);

  EXPECT_NEAR(x(0, 0), 1.0, 1e-9);
  EXPECT_NEAR(x(1, 0), 1.0, 1e-9);
}

TEST(MatrixTest, SolvesIdentityMatrix) {
  Matrix A = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
  Matrix f = {2.0, 3.0, 4.0};

  Matrix x = solve(A, f);

  EXPECT_NEAR(x(0, 0), 2.0, 1e-9);
  EXPECT_NEAR(x(1, 0), 3.0, 1e-9);
  EXPECT_NEAR(x(2, 0), 4.0, 1e-9);
}

TEST(MatrixTest, ThrowsOnSingularMatrix) {
  Matrix A = {{1.0, 2.0}, {2.0, 4.0}};
  Matrix f = {5.0, 10.0};

  EXPECT_THROW(solve(A, f), std::runtime_error);
}

TEST(MatrixTest, ThrowsWhenInconsistentSystem) {
  Matrix A = {{1.0, 1.0}, {1.0, 1.0}};
  Matrix f = {
      2.0, 3.0 // противоречие
  };

  EXPECT_THROW(solve(A, f), std::runtime_error);
}

TEST(MatrixTest, SolvesLargerSystem) {
  Matrix A = {{3, 2, -1}, {2, -2, 4}, {-1, 0.5, -1}};
  Matrix f = {1, -2, 0};
  Matrix x = solve(A, f);

  EXPECT_NEAR(x(0, 0), 1.0, 1e-9);
  EXPECT_NEAR(x(1, 0), -2.0, 1e-9);
  EXPECT_NEAR(x(2, 0), -2.0, 1e-9);
}

TEST(MatrixTest, 4x4SLAU) {
  std::cout.precision(2);

  Matrix A = {{2, 1, -1, 3}, {1, 2, 3, 2}, {3, -1, -1, 4}, {2, 3, 2, 1}};

  Matrix b = {4, 16, 2, 15};
  Matrix c = {1.0, 2.0, 3.0, 1.0};

  EXPECT_TRUE(solve(A, b) == c);
}
