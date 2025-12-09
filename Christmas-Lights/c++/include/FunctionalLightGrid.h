#pragma once

#include "LightGrid.h"

#include <ostream>
#include <string>

class FunctionalLightGrid : public LightGrid
{
public:
    static LightGrid *start(size_t maxX, size_t maxY);
    
    LightGrid *toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    LightGrid *turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    LightGrid *turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY) override final;
    
protected: 
    using LightGrid::LightGrid;
};
