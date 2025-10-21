//
// Created by Anna on 16.10.25.
//

#include <gtest/gtest.h>
#include <iomanip>
#include <matrix.h>

using namespace linalg;

TEST(MatrixTest, ReshapeIncrease) {
  Matrix m(2, 2);
  m.begin()[0] = 1;
  m.begin()[1] = 2;

  m.reshape(3, 3);

  EXPECT_EQ(m.rows(), 3);
  EXPECT_EQ(m.columns(), 3);
  EXPECT_EQ(m.capacity(), 9);
}

TEST(MatrixTest, ReshapeDecrease) {
  Matrix m(3, 3);
  m.begin()[0] = 5;

  m.reshape(2, 2);

  EXPECT_EQ(m.rows(), 2);
  EXPECT_EQ(m.columns(), 2);
  EXPECT_EQ(m.capacity(), 9);
}

TEST(MatrixTest, ReserveIncrease) {
  Matrix m(2, 2);
  auto old_ptr = m.begin();
  m.reserve(10);

  EXPECT_GE(m.capacity(), 10);
  EXPECT_EQ(m.rows(), 2);
  EXPECT_EQ(m.columns(), 2);
  EXPECT_NE(m.begin(), old_ptr);
}

TEST(MatrixTest, ReserveLessOrEqual) {
  Matrix m(2, 2);
  auto old_ptr = m.begin();
  m.reserve(3);
  EXPECT_EQ(m.begin(), old_ptr);
}

TEST(MatrixTest, ClearMatrix) {
  Matrix m(3, 4);
  m.clear();

  EXPECT_EQ(m.rows(), 0);
  EXPECT_EQ(m.columns(), 0);
  EXPECT_TRUE(m.empty());
  EXPECT_NE(m.begin(), nullptr);
}

TEST(MatrixTest, ShrinkToFitNotEmpty) {
  Matrix m(3, 3);
  m.reshape(2, 2);
  auto old_ptr = m.begin();
  m.shrink_to_fit();

  EXPECT_EQ(m.capacity(), 4);
  EXPECT_EQ(m.size(), 4);
  EXPECT_NE(m.begin(), old_ptr);
}

TEST(MatrixTest, ShrinkToFitEmpty) {
  Matrix m;
  m.shrink_to_fit();

  EXPECT_EQ(m.capacity(), 0);
  EXPECT_EQ(m.begin(), nullptr);
}

TEST(MatrixTest, SwapMatrices) {
  Matrix m1(2, 2);
  m1.begin()[0] = 1;

  Matrix m2(3, 3);
  m2.begin()[0] = 9;

  m1.swap(m2);

  EXPECT_EQ(m1.rows(), 3);
  EXPECT_EQ(m1.columns(), 3);
  EXPECT_EQ(m1.begin()[0], 9);

  EXPECT_EQ(m2.rows(), 2);
  EXPECT_EQ(m2.columns(), 2);
  EXPECT_EQ(m2.begin()[0], 1);
}

TEST(MatrixTest, LUTest) {
  Matrix A = {{2, 3, 1}, {4, 7, 2}, {6, 18, 5}};
  std::pair<Matrix, Matrix> pair = A.lu_decompose();
  EXPECT_TRUE(A == pair.first * pair.second);
}

TEST(MatrixTest, LUTest2) {
  Matrix A = {{2, 1, 1}, {4, 3, 3}, {8, 7, 9}};
  std::pair<Matrix, Matrix> pair = A.lu_decompose();
  EXPECT_TRUE(A == pair.first * pair.second);
}

TEST(MatrixTest, SingularMatricesLU) {
  Matrix zero_pivot = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

  Matrix becomes_singular = {{1, 2, 3}, {2, 4, 6}, {7, 8, 9}};
  EXPECT_THROW(zero_pivot.lu_decompose(), std::runtime_error);
  EXPECT_THROW(becomes_singular.lu_decompose(), std::runtime_error);
}

TEST(MatrixTest, NotSquareMatrixLU) {
  Matrix not_square = {{1, 2, 3}, {4, 5, 6}};
  EXPECT_THROW(not_square.lu_decompose(), std::runtime_error);
}
TEST(MatrixTest, EmpltyMatrixLU) {
  Matrix empty_matrix(3, 3);
  EXPECT_THROW(empty_matrix.lu_decompose(), std::runtime_error);
}