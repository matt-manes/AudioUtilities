#pragma once

#include "Range.h"
#include <cmath>

namespace AudioUtilities
{
    namespace Clamp
    {
        // Clamp `val` within `range`.
        float clamp(float val, Range::Range<float> range);

        // Clamp `val` within the range `min` to `max`.
        float clamp(float val, float min, float max);
    } // namespace Clamp
} // namespace AudioUtilities
