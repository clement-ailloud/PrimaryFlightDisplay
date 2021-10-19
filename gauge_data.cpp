/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include <iostream>
#include <string>
#include <vector>

#include "gauge_data.h"

int main()
{
    GaugeData* gaugeData = new GaugeDataInt();

    for (auto i = 0ul; i < 5; ++i)
        gaugeData->push(i);

    for (auto i = 0ul; i < 5; ++i)
        std::cout << gaugeData[i] << '\n';
}
