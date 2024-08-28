#pragma once

#include "Clamp.h"

namespace AudioUtilities
{
    namespace Polarity
    {
        // Convert a value from a -1 to 1 scale to 0 to 1 scale.
        inline float bipolarToUnipolar(float val)
        {
            return Clamp::clamp((val + 1.0f) * 0.5f, 0.0f, 1.0f);
        }

        // Convert a value from a 0 to 1 scale to a -1 to 1 scale.
        inline float unipolarToBipolar(float val)
        {
            return Clamp::clamp((val * 2.0f) - 1.0f, -1.0f, 1.0f);
        }
    } // namespace Polarity
} // namespace AudioUtilities