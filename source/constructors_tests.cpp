//
// Created by Anna on 8.10.25.
//
#include <gtest/gtest.h>
#include <matrix.h>

using namespace linalg;

TEST(MatrixTest, DefaultConstructor) {
  Matrix m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.rows(), 0);
  EXPECT_EQ(m.columns(), 0);
}

TEST(MatrixTest, ConstructorWithParametres) {
  Matrix m(3, 4);
  EXPECT_EQ(m.rows(), 3);
  EXPECT_EQ(m.columns(), 4);
  EXPECT_FALSE(m.empty());
}

TEST(MatrixTest, ConstructorWithParametr) {
  Matrix m(6);
  EXPECT_EQ(m.rows(), 6);
  EXPECT_EQ(m.columns(), 1);
  EXPECT_FALSE(m.empty());
}

TEST(MatrixTest, CopyConstructor) {
  Matrix original(2, 3);

  for (size_t i = 0; i < original.size(); ++i)
    original.begin()[i] = (double)i + 1;

  Matrix copy(original);

  EXPECT_EQ(copy.rows(), original.rows());
  EXPECT_EQ(copy.columns(), original.columns());
  EXPECT_EQ(copy.capacity(), original.capacity());

  for (size_t i = 0; i < original.size(); ++i)
    EXPECT_EQ(copy.begin()[i], original.begin()[i]);

  EXPECT_NE(copy.begin(), original.begin());
}

TEST(MatrixTest, MoveConstructor) {
  Matrix temp(2, 2);
  temp.begin()[0] = 1;
  temp.begin()[1] = 2;
  temp.begin()[2] = 3;
  temp.begin()[3] = 4;

  double *old_ptr = temp.begin();

  Matrix moved(std::move(temp));

  EXPECT_EQ(moved.rows(), 2);
  EXPECT_EQ(moved.columns(), 2);
  EXPECT_EQ(moved.capacity(), 4);
  EXPECT_EQ(moved.begin()[0], 1);
  EXPECT_EQ(moved.begin()[3], 4);

  EXPECT_EQ(moved.begin(), old_ptr);

  EXPECT_EQ(temp.begin(), nullptr);
  EXPECT_EQ(temp.rows(), 0);
  EXPECT_EQ(temp.columns(), 0);
  EXPECT_EQ(temp.capacity(), 0);
}

TEST(MatrixTest, InitializerListConstructor2D) {
  Matrix m{{1, 2, 3}, {4, 5, 6}};

  EXPECT_EQ(m.rows(), 2);
  EXPECT_EQ(m.columns(), 3);
  EXPECT_EQ(m.capacity(), 6);
  EXPECT_FALSE(m.empty());

  EXPECT_EQ(m.begin()[0], 1);
  EXPECT_EQ(m.begin()[1], 2);
  EXPECT_EQ(m.begin()[2], 3);
  EXPECT_EQ(m.begin()[3], 4);
  EXPECT_EQ(m.begin()[4], 5);
  EXPECT_EQ(m.begin()[5], 6);
}

TEST(MatrixTest, InitializerListConstructor2D_Empty) {
  Matrix m{};

  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.rows(), 0);
  EXPECT_EQ(m.columns(), 0);
  EXPECT_EQ(m.capacity(), 0);
  EXPECT_EQ(m.begin(), nullptr);
}

TEST(MatrixTest, InitializerListConstructor2D_InvalidRowSize) {
  EXPECT_THROW(
    Matrix m({{1, 2}, {3, 4, 5}}),
    std::runtime_error
  );
}

TEST(MatrixTest, InitializerListConstructor1D) {
  Matrix v{1, 2, 3, 4};

  EXPECT_EQ(v.rows(), 4);
  EXPECT_EQ(v.columns(), 1);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_FALSE(v.empty());

  EXPECT_EQ(v.begin()[0], 1);
  EXPECT_EQ(v.begin()[1], 2);
  EXPECT_EQ(v.begin()[2], 3);
  EXPECT_EQ(v.begin()[3], 4);
}

TEST(MatrixTest, InitializerListConstructor1D_Empty) {
  Matrix v{};

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.rows(), 0);
  EXPECT_EQ(v.columns(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.begin(), nullptr);
}

