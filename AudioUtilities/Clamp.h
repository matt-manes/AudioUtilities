#pragma once

#include "Range.h"
#include <cmath>

namespace AudioUtilities
{
    namespace Clamp
    {
        // Clamp `val` within `range`.
        template <typename T> inline T clamp(T val, Range::Range<T> range)
        {
            if (range.contains(val)) { return val; }

            // By using absolute value of deltas we account for min value being
            // greater than max
            T startDelta = std::abs(val - range.getStart());
            T stopDelta = std::abs(val - range.getStop());
            // `val` is outside of range and closer to `range.start`
            if (startDelta < stopDelta) { return range.getStart(); }
            // `val` is outside of range and closer to `range.stop`
            return range.getStop();
        }

        // Clamp `val` within the range `min` to `max`.
        template <typename T> inline T clamp(T val, T min, T max)
        {
            Range::Range<T> range(min, max);
            return clamp(val, range);
        }
    } // namespace Clamp
} // namespace AudioUtilities
