#include "VectorLightGrid.h"

#include <iostream>
#include <sstream>

LightGrid *VectorLightGrid::start(size_t maxX, size_t maxY)
{
    return new VectorLightGrid{maxX, maxY};
}

VectorLightGrid::VectorLightGrid(size_t maxX, size_t maxY)
    : LightGrid{maxX, maxY}, m_grid{maxX + 1}, m_brightness{maxX + 1}
{
    for (size_t x{0}; x <= maxX; ++x)
    {
        m_grid.at(x).resize(maxY + 1);
        m_brightness.at(x).resize(maxY + 1);
    }
}

size_t VectorLightGrid::getBrightness(size_t x, size_t y) const
{
    return m_brightness[x][y];
}

bool VectorLightGrid::isOn(size_t x, size_t y) const
{
    return m_grid[x][y];
}

LightGrid *VectorLightGrid::toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
{
    for (size_t x{topLeftX}; x <= bottomRightX; ++x)
    {
        for (size_t y{topleftY}; y <= bottomRightY; ++y)
        {
            m_brightness[x][y] += 2;
            m_grid[x][y] = !m_grid[x][y];
        }
    }

    return this;
}

LightGrid *VectorLightGrid::turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
{
    for (size_t x{topLeftX}; x <= bottomRightX; ++x)
    {
        for (size_t y{topleftY}; y <= bottomRightY; ++y)
        {
            size_t brightess{m_brightness[x][y]};
            if (brightess > 0)
            {
                --brightess;
            }
            else
            {
                brightess = 0;
            }
            m_brightness[x][y] = brightess;
            m_grid[x][y] = false;
        }
    }

    return this;
}

LightGrid *VectorLightGrid::turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
{
    for (size_t x{topLeftX}; x <= bottomRightX; ++x)
    {
        for (size_t y{topleftY}; y <= bottomRightY; ++y)
        {
            ++m_brightness[x][y];
            m_grid[x][y] = true;
        }
    }

    return this;
}
