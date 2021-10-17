/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "math/functions.h"

#include <cassert>
#include <cmath>

namespace Common
{
namespace Math
{

float floor(float value, float interval)
{
    assert(interval != 0);
    return value - std::fmod(value, interval);
}

float ceil(float value, float interval)
{
    assert(interval != 0);
    return value + interval - std::fmod(value, interval);
}

} // namespace Math
} // namespace Common
