#include <gtest/gtest.h>
#include <matrix.h>
#include <sstream>

using namespace linalg;

TEST(IstreamTest, ValidMatrix)
{
    std::stringstream ss("| 1 2 | | 3 4 |");
    Matrix m;
    ss >> m;
    Matrix expected = {{1, 2}, {3, 4}};
    ASSERT_EQ(m, expected);
}

TEST(IstreamTest, ValidMatrixWithNewlines)
{
    std::stringstream ss(" | 1 2 | \n | 3 4 | ");
    Matrix m;
    ss >> m;
    Matrix expected = {{1, 2}, {3, 4}};
    ASSERT_EQ(m, expected);
}

TEST(IstreamTest, MissingClosingPipe)
{
    std::stringstream ss("| 1 2 | | 3 4 ");
    Matrix m;
    ASSERT_THROW(ss >> m, std::runtime_error);
}

TEST(IstreamTest, InconsistentColumnCount)
{
    std::stringstream ss("| 1 2 | | 3 4 5 |");
    Matrix m;
    ASSERT_THROW(ss >> m, std::runtime_error);
}

TEST(IstreamTest, MissingOpeningPipe)
{
    std::stringstream ss("1 2 | | 3 4 |");
    Matrix m;
    ASSERT_THROW(ss >> m, std::runtime_error);
}

TEST(IstreamTest, EmptyInput)
{
    std::stringstream ss("");
    Matrix m;
    ss >> m;
    ASSERT_TRUE(m.empty());
}

TEST(IstreamTest, CompletelyEmptyInput)
{
    std::stringstream ss("   ");
    Matrix m;
    ss >> m;
    ASSERT_TRUE(m.empty());
}

TEST(IstreamTest, SingleRow)
{
    std::stringstream ss("| 1 2 3 |");
    Matrix m;
    ss >> m;
    Matrix expected = {{1, 2, 3}};
    ASSERT_EQ(m, expected);
}

TEST(IstreamTest, EmptyRowInMiddle)
{
    std::stringstream ss("| 1 2 | | | | 3 4 |");
    Matrix m;
    ASSERT_THROW(ss >> m, std::runtime_error);
}

TEST(IstreamTest, InvalidCharacter)
{
    std::stringstream ss("| 1 2 | | 3 a |");
    Matrix m;
    ASSERT_THROW(ss >> m, std::runtime_error);
}

TEST(IstreamTest, EmptyMatrixMultipleRows)
{
    std::stringstream ss("| | | |");
    Matrix m;
    ASSERT_THROW(ss >> m, std::runtime_error);
}
