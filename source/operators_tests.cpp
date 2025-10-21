//
// Created by Anna Dolgopolova on 16.10.2025.
//

#include <gtest/gtest.h>
#include <matrix.h>

using namespace linalg;

TEST(MatrixTest, CopyAssignment) {
  Matrix m1(3, 3);
  for (std::size_t i = 0; i < 9; ++i) {
    m1.begin()[i] = (double)i;
  }

  Matrix m2(2, 2);
  m2 = m1;
  EXPECT_NE(m1.begin(), m2.begin());
  EXPECT_EQ(m2.rows(), 3);
  EXPECT_EQ(m2.columns(), 3);
  EXPECT_DOUBLE_EQ(*m2.begin(), 0.0);
  EXPECT_DOUBLE_EQ(m2.begin()[8], 8.0);

  m1.begin()[0] = 999.0;
  EXPECT_DOUBLE_EQ(m2.begin()[0], 0.0);
}

TEST(MatrixTest, SelfAssignment) {
  Matrix m(3, 3);
  for (std::size_t i = 0; i < 9; ++i) {
    m.begin()[i] = (double)i;
  }

  auto old_ptr = m.begin();
  m = m;
  EXPECT_EQ(m.begin(), old_ptr);

  EXPECT_EQ(m.rows(), 3);
  EXPECT_EQ(m.columns(), 3);
  EXPECT_DOUBLE_EQ(m.begin()[0], 0.0);
}

TEST(MatrixTest, MoveAssignment) {
  Matrix m1(3, 3);
  for (std::size_t i = 0; i < 9; ++i) {
    m1.begin()[i] = (double)i;
  }

  auto old_ptr = m1.begin();

  Matrix m2(2, 2);
  m2 = std::move(m1);

  EXPECT_EQ(m2.rows(), 3);
  EXPECT_EQ(m2.columns(), 3);
  EXPECT_EQ(m2.begin(), old_ptr);
  EXPECT_DOUBLE_EQ(m2.begin()[5], 5.0);
}

TEST(MatrixTest, AssignmentWithCapacityReuse) {
  Matrix m1(3, 3);
  Matrix m2(2, 2);

  std::size_t old_capacity = m1.capacity();

  m1 = m2;

  EXPECT_EQ(m1.capacity(), old_capacity);
  EXPECT_EQ(m1.rows(), 2);
  EXPECT_EQ(m1.columns(), 2);
}

TEST(MatrixTest, UnaryPlus) {
  Matrix m = {{1, 2}, {3, 4}};
  Matrix result = +m;
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST(MatrixTest, UnaryMinus) {
  Matrix m = {{1, 2}, {3, 4}};
  Matrix result = -m;
  EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -4.0);
}

TEST(MatrixTest, Addition) {
  Matrix a = {{1, 2}, {3, 4}};
  Matrix b = {{5, 6}, {7, 8}};
  Matrix c = a + b;
  EXPECT_DOUBLE_EQ(c(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(c(1, 1), 12.0);
}

TEST(MatrixTest, MultiplicationScalar) {
  Matrix m = {{1, 2}, {3, 4}};
  Matrix r1 = m * 2.0;
  Matrix r2 = 2.0 * m;
  EXPECT_DOUBLE_EQ(r1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(r2(1, 1), 8.0);
}

TEST(MatrixTest, Equality) {
  Matrix a = {{1.0, 2.0}, {3.0, 4.0}};
  Matrix b = {{1.0, 2.0}, {3.0, 4.0}};
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(MatrixTest, AdditionDimensionMismatch) {
  Matrix a(2, 2);
  Matrix b(3, 3);
  EXPECT_THROW(a += b, std::runtime_error);
}

TEST(MatrixTest, EmptyMatrixOutput) {
  Matrix m;
  std::ostringstream oss;
  oss << m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(oss.str(), "");
}

// оператор [] для неконстантной матрицы
TEST(MatrixTest, SquareBracketOperator) {
  Matrix m = {{1.0, 2.0, 3.0},
              {4.0, 5.0, 6.0}};

  // Проверка чтения
  EXPECT_DOUBLE_EQ(m[0][0], 1.0);
  EXPECT_DOUBLE_EQ(m[0][1], 2.0);
  EXPECT_DOUBLE_EQ(m[1][2], 6.0);

  // Проверка записи
  m[0][0] = 10.0;
  EXPECT_DOUBLE_EQ(m[0][0], 10.0);
  EXPECT_DOUBLE_EQ(m(0, 0), 10.0);
}

// проверка оператора [] для константной матрицы
TEST(MatrixTest, SquareBracketOperatorConst) {
  const Matrix m = {{1.0, 2.0, 3.0},
                    {4.0, 5.0, 6.0}};

  EXPECT_DOUBLE_EQ(m[0][0], 1.0);
  EXPECT_DOUBLE_EQ(m[1][1], 5.0);

}

TEST(MatrixTest, SquareBracketOperatorOutOfRange) {
  Matrix m = {{1.0, 2.0}, {3.0, 4.0}};

  // проверяем, что при выходе за границы матрицы, выбрасывается исключение
  EXPECT_THROW(m[2][0], std::runtime_error);
  EXPECT_THROW(m[100][0], std::runtime_error);
  EXPECT_THROW(m[0][2], std::runtime_error);
  EXPECT_THROW(m[1][5], std::runtime_error);
}

// проверяем [] через ()
TEST(MatrixTest, SquareBracketOperatorConsistencyWithParentheses) {
  Matrix m = {{1.1, 2.2}, {3.3, 4.4}};

  EXPECT_DOUBLE_EQ(m[0][0], m(0, 0));
  EXPECT_DOUBLE_EQ(m[1][1], m(1, 1));

  m[0][1] = 99.9;
  EXPECT_DOUBLE_EQ(m(0, 1), 99.9);

  m(1, 0) = 88.8;
  EXPECT_DOUBLE_EQ(m[1][0], 88.8);
}