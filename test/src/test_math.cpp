/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "common/functions.h"

#include "gtest/gtest.h"

using namespace testing;

TEST(TestMath, floor)
{
    EXPECT_FLOAT_EQ(Common::Math::floor(0.f, 10.f), 0.f);
    EXPECT_FLOAT_EQ(Common::Math::floor(7.f, 10.f), 0.f);
    EXPECT_FLOAT_EQ(Common::Math::floor(10.f, 10.f), 10.f);
    EXPECT_FLOAT_EQ(Common::Math::floor(13.f, 10.f), 10.f);
    EXPECT_FLOAT_EQ(Common::Math::floor(13.f, 15.f), 0.f);
    EXPECT_FLOAT_EQ(Common::Math::floor(18.f, 15.f), 15.f);
}

TEST(TestMath, ceil)
{
    EXPECT_FLOAT_EQ(Common::Math::ceil(0.f, 10.f), 10.f);
    EXPECT_FLOAT_EQ(Common::Math::ceil(7.f, 10.f), 10.f);
    EXPECT_FLOAT_EQ(Common::Math::ceil(10.f, 10.f), 20.f);
    EXPECT_FLOAT_EQ(Common::Math::ceil(13.f, 10.f), 20.f);
    EXPECT_FLOAT_EQ(Common::Math::ceil(13.f, 15.f), 15.f);
    EXPECT_FLOAT_EQ(Common::Math::ceil(18.f, 15.f), 30.f);
}

int main(int argc, char* argv[])
{
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
