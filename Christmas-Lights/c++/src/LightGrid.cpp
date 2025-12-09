#include "LightGrid.h"

#include <iomanip>
#include <iostream>
#include <typeinfo> 

LightGrid::LightGrid(size_t maxX, size_t maxY)
    : m_maxX{maxX}, m_maxY{maxY}
{
}

size_t LightGrid::getCountOfLightsOn() const
{
    size_t countOfLightsOn{0};
    for (size_t x{0}; x <= m_maxX; ++x)
    {
        for (size_t y{0}; y <= m_maxY; ++y)
        {
            if (isOn(x, y))
            {
                ++countOfLightsOn;
            }
        }
    }

    return countOfLightsOn;
}

size_t LightGrid::getTotalBrightness() const
{
    size_t totalBrightness{0};
    for (size_t x = 0; x <= m_maxX; ++x)
    {
        for (size_t y = 0; y <= m_maxY; ++y)
        {
            totalBrightness += getBrightness(x, y);
        }
    }

    return totalBrightness;
}

const LightGrid *LightGrid::showSummary() const
{
    std::cout << typeid(*this).name()
              << " lights on: " << std::setw(6) << getCountOfLightsOn()
              << " | total brightness: " << std::setw(12) << getTotalBrightness()
              << std::endl;

    return this;
}