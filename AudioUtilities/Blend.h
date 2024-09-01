#pragma once

#include "Clamp.h"
#include "Polarity.h"

namespace AudioUtilities
{
    namespace Blend
    {
        // Returns a blended value between `val1` and `val2` according to
        // `control`. `control` is clamped to the range `0.0<->1.0`.
        float blend(float val1, float val2, float control);

        // Returns a blended value between `val1` and `val2` according to
        // `control`. `control` is clamped to the range `-1.0<->1.0`.
        float bipolarBlend(float val1, float val2, float control);
    } // namespace Blend
} // namespace AudioUtilities