#pragma once

#include "LightGrid.h"

#include <ostream>
#include <string>
#include <vector>

class VectorLightGrid final : public LightGrid
{
public:
    static LightGrid *start(size_t maxX, size_t maxY);

    VectorLightGrid(size_t maxX, size_t maxY);

    size_t getBrightness(size_t x, size_t y) const override;
    bool isOn(size_t x, size_t y) const override;

    LightGrid *toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    LightGrid *turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    LightGrid *turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;

private:
    std::vector<std::vector<bool>> m_grid;
    std::vector<std::vector<size_t>> m_brightness;
};
