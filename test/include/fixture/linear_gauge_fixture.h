/**
 * @file linear_gauge_fixture.h
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#ifndef LINEAR_GAUGE_FIXTURE
#define LINEAR_GAUGE_FIXTURE

#include "gtest/gtest.h"

/**
 * @brief see test with param (TEST_P)
 */

class LinearGaugeFixture : public testing::Test
{
    void SetUp() override {}
    void TearDown() override {}

  protected:
    int m_width, m_height;
};

#endif
