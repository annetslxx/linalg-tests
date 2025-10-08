//
// Created by Anna on 8.10.25.
//
#include <gtest/gtest.h>
#include <matrix.h>
#include <iostream>

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

