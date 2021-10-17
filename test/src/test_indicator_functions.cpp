/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "indicator/indicator_functions.h"

#include "gtest/gtest.h"

#define EXPECT_CONTAINER_EQ(lhs, rhs)                                                              \
    ASSERT_EQ(lhs.size(), rhs.size());                                                             \
    for (auto i = 0ul; i < lhs.size(); ++i)                                                        \
        EXPECT_EQ(lhs[i], rhs[i]);

using namespace testing;

TEST(TestIndicatorFunctions, test_textWidth)
{
    EXPECT_EQ(textWidth(""), 1);
    // EXPECT_EQ(textWidth("Hello"), 0);
    // EXPECT_EQ(textWidth("world"), 0);
    // EXPECT_EQ(textWidth("Hello world"), 0);
}

TEST(TestIndicatorFunctions, test_setTicksLabelValue)
{
    // Dummy case
    {
        std::vector<int> labels;
        EXPECT_DEATH(setTicksLabelValue(labels, 0, 0, 0), "");
    }
    // Dummy case
    {
        std::vector<int> labels;
        EXPECT_DEATH(setTicksLabelValue(labels, 0, -1, 0), "");
    }
    // Dummy case
    {
        std::vector<int> labels;
        setTicksLabelValue(labels, 0, 1, 0);

        std::vector<int> expected;
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    {
        std::vector<int> labels(3, 0);
        setTicksLabelValue(labels, 0, 10, 3);

        std::vector<int> expected{ 10, 0, -10 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    // Value close to interval
    {
        std::vector<int> labels(3, 0);
        setTicksLabelValue(labels, 9, 10, 3);

        std::vector<int> expected{ 10, 0, -10 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    // Value equal to interval
    {
        std::vector<int> labels(3, 0);
        setTicksLabelValue(labels, 10, 10, 3);

        std::vector<int> expected{ 20, 10, 0 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    // Value exceeds interval
    {
        std::vector<int> labels(3, 0);
        setTicksLabelValue(labels, 11, 10, 3);

        std::vector<int> expected{ 20, 10, 0 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
}

int main(int argc, char* argv[])
{
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
