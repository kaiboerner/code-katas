#include "ArrayLightGrid.h"

LightGrid *ArrayLightGrid::start(size_t maxX, size_t maxY)
{
    return new ArrayLightGrid{maxX, maxY};
}

ArrayLightGrid::ArrayLightGrid(size_t maxX, size_t maxY)
    : LightGrid{maxX, maxY}, m_grid{new bool *[maxX + 1] {}}, m_brightness{new size_t *[maxX + 1] {}}
{
    for (size_t i{}; i <= maxX; ++i)
    {
        m_grid[i] = new bool[maxY + 1]{};
        m_brightness[i] = new size_t[maxY + 1]{};
    }
}

ArrayLightGrid::~ArrayLightGrid()
{
    for (size_t i{}; i <= m_maxX; ++i)
    {
        delete[] m_grid[i];
        delete[] m_brightness[i];
    }

    delete[] m_grid;
    delete[] m_brightness;
}

size_t ArrayLightGrid::getBrightness(size_t x, size_t y) const
{
    return m_brightness[x][y];
}

bool ArrayLightGrid::isOn(size_t x, size_t y) const
{
    return m_grid[x][y];
}

LightGrid *ArrayLightGrid::toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
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

LightGrid *ArrayLightGrid::turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
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

LightGrid *ArrayLightGrid::turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
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