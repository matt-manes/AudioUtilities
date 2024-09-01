#pragma once

#include "Clamp.h"

namespace AudioUtilities
{
    namespace Polarity
    {
        // Convert a value from a -1 to 1 scale to 0 to 1 scale.
        float bipolarToUnipolar(float val);

        // Convert a value from a 0 to 1 scale to a -1 to 1 scale.
        float unipolarToBipolar(float val);

    } // namespace Polarity
} // namespace AudioUtilities