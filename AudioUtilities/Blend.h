#pragma once

#include "Clamp.h"
#include "Polarity.h"

namespace AudioUtilities
{
    namespace Blend
    {
        // Returns a blended value between `val1` and `val2` according to
        // `control`. `control` is clamped to the range `0.0<->1.0`.
        template <typename T> inline T blend(T val1, T val2, float control)
        {
            return val1 + (Clamp::clamp(control, 0.0f, 1.0f) * (val2 - val1));
        }

        // Returns a blended value between `val1` and `val2` according to
        // `control`. `control` is clamped to the range `-1.0<->1.0`.
        template <typename T>
        inline T bipolarBlend(T val1, T val2, float control)
        {
            return blend(val1, val2, Polarity::bipolarToUnipolar(control));
        }
    } // namespace Blend
} // namespace AudioUtilities