//
// Created by Anna on 16.10.25.
//

#include <gtest/gtest.h>
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