#pragma once

#include "LightGrid.h"

#include <iostream>
#include <sstream>
#include <string>

class ArrayLightGrid final : public LightGrid
{
public:
    static LightGrid *start(size_t maxX, size_t maxY);

    ArrayLightGrid(size_t maxX, size_t maxY);
    ~ArrayLightGrid() override;

    size_t getBrightness(size_t x, size_t y) const override;
    bool isOn(size_t x, size_t y) const override;

    LightGrid *toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    LightGrid *turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    LightGrid *turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;

private:
    bool **m_grid;
    size_t **m_brightness;
};
