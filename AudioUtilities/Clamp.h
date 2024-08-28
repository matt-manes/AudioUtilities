#pragma once

#include "Range.h"

namespace AudioUtilities
{
    namespace Clamp
    {
        // Clamp `val` within the range `min` to `max`.
        template <typename T> inline T clamp(T val, T min, T max)
        {
            if (val < min) { return min; }
            if (max < val) { return max; }
            return val;
        }

        // Clamp `val` within `range`.
        template <typename T> inline T clamp(T val, Range::Range<T> range)
        {
            return clamp(val, range.getStart(), range.getStop());
        }
    } // namespace Clamp
} // namespace AudioUtilities
