/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

enum BorderPositionFlags
{
    NoBorder = 1 << 0,
    BorderLeft = 1 << 1,
    BorderRight = 1 << 2,
    BorderTop = 1 << 3,
    BorderBottom = 1 << 4
};
using BorderPosition = BorderPositionFlags;
