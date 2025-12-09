#pragma once

#include <cstdlib>

class LightGrid
{
public:
    const size_t m_maxX;
    const size_t m_maxY;

    virtual ~LightGrid() = default

    virtual size_t getBrightness(size_t x, size_t y) const = 0;
    size_t getCountOfLightsOn() const;
    size_t getTotalBrightness() const;
    virtual bool isOn(size_t x, size_t y) const = 0;
    const LightGrid *showSummary() const;

    virtual LightGrid *toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) = 0;
    virtual LightGrid *turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) = 0;
    virtual LightGrid *turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) = 0;

protected:
    LightGrid(size_t maxX, size_t maxY);
};