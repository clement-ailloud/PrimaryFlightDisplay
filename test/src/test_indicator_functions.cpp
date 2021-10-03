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

using namespace testing;

TEST(TestIndicatorFunctions, test_textWidth)
{
    EXPECT_EQ(textWidth(""), 1);
    EXPECT_EQ(textWidth("Hello"), 0);
    EXPECT_EQ(textWidth("world"), 0);
    EXPECT_EQ(textWidth("Hello world"), 0);
}

int main(int argc, char* argv[])
{
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
