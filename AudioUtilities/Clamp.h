#pragma once

#include "Range.h"
#include <cmath>

namespace AudioUtilities
{
    namespace Clamp
    {
        // Clamp `val` within `range`.
        template <typename T> inline T clamp(T value, Range::Range<T> range)
        {
            if (range.contains(value)) { return value; }

            // By using absolute value of deltas we account for min value being
            // greater than max
            T startDelta = std::abs(value - range.getStart());
            T stopDelta = std::abs(value - range.getStop());
            // `value` is outside of range and closer to `range.start`
            if (startDelta < stopDelta) { return range.getStart(); }
            // `value` is outside of range and closer to `range.stop`
            return range.getStop();
        }

        // Clamp `value` within the range `min` to `max`.
        template <typename T> inline T clamp(T value, T min, T max)
        {
            Range::Range<T> range(min, max);
            return clamp(value, range);
        }
    } // namespace Clamp
} // namespace AudioUtilities
