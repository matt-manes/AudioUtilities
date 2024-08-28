#pragma once

#include "Range.h"

namespace AudioUtilities
{
    namespace Scale
    {
        float scale(
            float value, float oldMin, float oldMax, float newMin, float newMax
        );

        float scale(
            float value,
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
            inline float fromAToB(float value) const
            {
                return scale(value, a, b);
            }

            // Convert `value` from range `b` to range `a`.
            inline float fromBToA(float value) const
            {
                return scale(value, b, a);
            }
        };

    } // namespace Scale
} // namespace AudioUtilities