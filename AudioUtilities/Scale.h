#pragma once

#include "Range.h"

namespace AudioUtilities
{
    namespace Scale
    {
        // Scale `val` from old range to new range.
        float scale(
            float val, float oldMin, float oldMax, float newMin, float newMax
        );

        // Scale `val` from old range to new range.
        float scale(
            float val,
            Range::Range<float> oldRange,
            Range::Range<float> newRange
        );

        // Scale numers back and forth between two different ranges.
        class Scale
        {
          public:

            Scale() {}

            Scale(Range::Range<float> a, Range::Range<float> b);

            Range::Range<float> a, b;

            // Convert `value` from range `a` to range `b`.
            float fromAToB(float val) const;

            // Convert `value` from range `b` to range `a`.
            float fromBToA(float val) const;
        };

    } // namespace Scale
} // namespace AudioUtilities