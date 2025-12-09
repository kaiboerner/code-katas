#include "ArrayLightGrid.h"
#include "FunctionalLightGrid.h"
#include "VectorLightGrid.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>

namespace
{
    using milliseconds_t = unsigned long long;

    milliseconds_t getMilliseconds();

    constexpr int loops{100};

    template <class T>
    milliseconds_t processGrid();
}

int main()
{
    std::map<std::string, milliseconds_t> milliseconds;

    for (int i{}; i < loops; ++i)
    {
        std::cout << "Loop No.: " << (i + 1) << std::endl
                  << "==========" << std::endl
                  << std::endl;

        milliseconds["FunctionalLightGrid"] += processGrid<FunctionalLightGrid>();
        milliseconds["VectorLightGrid"] += processGrid<VectorLightGrid>();
        milliseconds["ArrayLightGrid"] += processGrid<ArrayLightGrid>();

        std::cout << std::endl;
    }

    std::cout << "Execution times:" << std::endl;
    for (auto mapEntry : milliseconds)
    {
        std::cout << std::setw(20) << mapEntry.first << ": " << std::setw(20) << (mapEntry.second / loops) << std::endl;
    }
}

namespace
{
    milliseconds_t getMilliseconds()
    {
        using namespace std::chrono;
        milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

        return static_cast<milliseconds_t>(ms.count());
    }

    template <class T>
    milliseconds_t processGrid()
    {
        milliseconds_t start = getMilliseconds();
        {
            LightGrid *grid = T::start(999, 999);

            delete grid
                ->turnOn(0, 0, 999, 999)
                ->toggle(0, 0, 999, 0)
                ->turnOff(499, 499, 500, 500)
                ->showSummary();
        }
        {
            LightGrid *grid = T::start(999, 999);

            delete grid
                ->turnOn(0, 0, 0, 0)
                ->toggle(0, 0, 999, 999)
                ->showSummary();
        }
        {
            LightGrid *grid = T::start(999, 999);

            delete grid
                ->turnOn(887, 9, 959, 629)
                ->turnOn(454, 398, 844, 448)
                ->turnOff(539, 243, 559, 965)
                ->turnOff(370, 819, 676, 868)
                ->turnOff(145, 40, 370, 997)
                ->turnOff(301, 3, 808, 453)
                ->turnOn(351, 678, 951, 908)
                ->toggle(720, 196, 897, 994)
                ->toggle(831, 394, 904, 860)
                ->showSummary();
        }
        return getMilliseconds() - start;
    }
}