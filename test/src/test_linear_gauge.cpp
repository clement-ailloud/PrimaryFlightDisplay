/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "fixture/linear_gauge_fixture.h"

/**
 * Slit draw methods for returning a vector of (x,y) coordinates.
 *
 * Draw methods/functions shall only get a vector of coordinates to draw ticks and labels.
 *
 * Example:
 *
 *      template <class X, class Y>
 *      using ScreenCoordinates = std::pair<X, Y>;
 *
 *      std::vector<ScreenCoordinates> largeTicksCoordinates;
 *      ...
 */

TEST_F(LinearGaugeFixture, test_getLargeTicksScreenCoordinates) {}

TEST_F(LinearGaugeFixture, test_getMiddleTicksScreenCoordinates) {}

TEST_F(LinearGaugeFixture, test_getSmallTicksScreenCoordinates) {}

TEST_F(LinearGaugeFixture, test_drawLargeTicksLabel) {}
