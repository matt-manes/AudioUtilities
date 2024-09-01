#pragma once

#include "Range.h"

namespace AudioUtilities
{
    namespace Scale
    {
        float scale(
            float val, float oldMin, float oldMax, float newMin, float newMax
        );

        float scale(
            float val,
            Range::Range<float> oldRange,
            Range::Range<float> newRange
        );

        class Scale
        {
          public:

            Scale() {}

            Scale(Range::Range<float> a, Range::Range<float> b)
            {
                this->a = a;
                this->b = b;
            }

            Range::Range<float> a, b;

            // Convert `value` from range `a` to range `b`.
            float fromAToB(float val) const { return scale(val, a, b); }

            // Convert `value` from range `b` to range `a`.
            float fromBToA(float val) const { return scale(val, b, a); }
        };

    } // namespace Scale
} // namespace AudioUtilities