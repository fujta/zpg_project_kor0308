#include "NumberGenerator.h"
#include <cstdlib>
#include <ctime>

float NumberGenerator::randomFloat(float min, float max)
{
    static bool first = true;

    if (first) {
        srand(static_cast<unsigned>(time(nullptr)));
        first = false;
    }

    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
