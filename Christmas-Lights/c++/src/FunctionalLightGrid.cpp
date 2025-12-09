#include "FunctionalLightGrid.h"

#include <iomanip>
#include <iostream>
#include <string>

namespace
{
    // declaration of helper classes

    class EmptyGrid final : public FunctionalLightGrid
    {
    public:
        EmptyGrid(size_t maxX, size_t maxY) : FunctionalLightGrid{maxX, maxY} {}

        size_t getBrightness(size_t x, size_t y) const override;
        bool isOn(size_t x, size_t y) const override;
    };

    class Rectangle final
    {
    public:
        Rectangle(
            size_t topLeftX,
            size_t topleftY,
            size_t bottomRightX,
            size_t bottomRightY);

        bool contains(size_t x, size_t y) const;

    private:
        const size_t m_topLeftX, m_topleftY, m_bottomRightX, m_bottomRightY;
    };

    class ModifiedLightGrid : public FunctionalLightGrid
    {
    public:
        ModifiedLightGrid(
            const FunctionalLightGrid *original,
            size_t topLeftX,
            size_t topleftY,
            size_t bottomRightX,
            size_t bottomRightY);

        ~ModifiedLightGrid();

        virtual size_t getBrightness(size_t x, size_t y) const override;
        virtual bool isOn(size_t x, size_t y) const override;

    protected:
        bool isSelected(size_t x, size_t y) const;

    private:
        const FunctionalLightGrid *m_original;
        const Rectangle m_selection;
    };

    class Toggle final : public ModifiedLightGrid
    {
    public:
        using ModifiedLightGrid::ModifiedLightGrid;

        size_t getBrightness(size_t x, size_t y) const override;
        bool isOn(size_t x, size_t y) const override;
    };

    class TurnOff final : public ModifiedLightGrid
    {
    public:
        using ModifiedLightGrid::ModifiedLightGrid;

        size_t getBrightness(size_t x, size_t y) const override;
        bool isOn(size_t x, size_t y) const override;
    };

    class TurnOn final : public ModifiedLightGrid
    {
    public:
        using ModifiedLightGrid::ModifiedLightGrid;

        size_t getBrightness(size_t x, size_t y) const override;
        bool isOn(size_t x, size_t y) const override;
    };

    // implementation of helper classes

    // implementation of EmptyGrid

    size_t EmptyGrid::getBrightness([[maybe_unused]] size_t x, [[maybe_unused]] size_t y) const
    {
        return 0;
    }

    bool EmptyGrid::isOn([[maybe_unused]] size_t x, [[maybe_unused]] size_t y) const
    {
        return false;
    }

    // implementation of ModifiedLightGrid

    ModifiedLightGrid::ModifiedLightGrid(
        const FunctionalLightGrid *original,
        size_t topLeftX,
        size_t topleftY,
        size_t bottomRightX,
        size_t bottomRightY)
        : FunctionalLightGrid{original->m_maxX, original->m_maxY}, m_original{original}, m_selection{topLeftX, topleftY, bottomRightX, bottomRightY}
    {
    }

    ModifiedLightGrid::~ModifiedLightGrid()
    {
        delete m_original;
    }

    size_t ModifiedLightGrid::getBrightness(size_t x, size_t y) const
    {
        return m_original->getBrightness(x, y);
    }

    bool ModifiedLightGrid::isOn(size_t x, size_t y) const
    {
        return m_original->isOn(x, y);
    }

    bool ModifiedLightGrid::isSelected(size_t x, size_t y) const
    {
        return m_selection.contains(x, y);
    }

    // implementation of Rectangle

    Rectangle::Rectangle(
        size_t topLeftX,
        size_t topleftY,
        size_t bottomRightX,
        size_t bottomRightY)
        : m_topLeftX(topLeftX), m_topleftY(topleftY), m_bottomRightX(bottomRightX), m_bottomRightY(bottomRightY)
    {
        if (topLeftX > bottomRightX || topleftY > bottomRightY)
        {
            throw std::invalid_argument("coordinates out of bounds");
        }
    }

    bool Rectangle::contains(size_t x, size_t y) const
    {
        return x >= m_topLeftX && x <= m_bottomRightX && y >= m_topleftY && y <= m_bottomRightY;
    }

    // implementation of Toggle

    size_t Toggle::getBrightness(size_t x, size_t y) const
    {
        size_t brightness{ModifiedLightGrid::getBrightness(x, y)};

        if (isSelected(x, y))
        {
            return brightness + 2;
        }

        return brightness;
    }

    bool Toggle::isOn(size_t x, size_t y) const
    {
        bool isOn = ModifiedLightGrid::isOn(x, y);

        if (isSelected(x, y))
        {
            return !isOn;
        }

        return isOn;
    }

    // implementation of TurnOff

    size_t TurnOff::getBrightness(size_t x, size_t y) const
    {
        size_t brightness{ModifiedLightGrid::getBrightness(x, y)};

        if (isSelected(x, y))
        {
            return brightness > 0 ? brightness - 1 : 0;
        }

        return brightness;
    }

    bool TurnOff::isOn(size_t x, size_t y) const
    {
        if (isSelected(x, y))
        {
            return false;
        }

        return ModifiedLightGrid::isOn(x, y);
    }

    // implementation of TurnOn

    size_t TurnOn::getBrightness(size_t x, size_t y) const
    {
        size_t brightness{ModifiedLightGrid::getBrightness(x, y)};

        if (isSelected(x, y))
        {
            return brightness + 1;
        }

        return brightness;
    }

    bool TurnOn::isOn(size_t x, size_t y) const
    {
        if (isSelected(x, y))
        {
            return true;
        }

        return ModifiedLightGrid::isOn(x, y);
    }

}

// implementation of FunctionalLightGrid

LightGrid *FunctionalLightGrid::start(size_t maxX, size_t maxY)
{
    return new EmptyGrid{maxX, maxY};
}

LightGrid *FunctionalLightGrid::toggle(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
{
    return new Toggle{this, topLeftX, topleftY, bottomRightX, bottomRightY};
}

LightGrid *FunctionalLightGrid::turnOff(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
{
    return new TurnOff{this, topLeftX, topleftY, bottomRightX, bottomRightY};
}

LightGrid *FunctionalLightGrid::turnOn(size_t topLeftX, size_t topleftY, size_t bottomRightX, size_t bottomRightY)
{
    return new TurnOn{this, topLeftX, topleftY, bottomRightX, bottomRightY};
}