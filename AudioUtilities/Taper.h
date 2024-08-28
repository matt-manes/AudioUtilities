#pragma once

#include "Range.h"
#include "Scale.h"
#include <cmath>

namespace AudioUtilities
{
    namespace Taper
    {
        enum Type
        {
            Log,
            Exp
        };

        /*
        Apply a taper curve to a value in order to produce log and exp style
        curves. A `curveFactor` value of `0.5` will produce a linear
        response, i.e. a waste of cpu cycles. Values between `0` and `0.5`
        will produce exponential curves and values between `0.5` and `1`
        will produce log curves.
        */
        class Taper
        {
          public:

            Taper();

            // Specify the expected minimum and maximum values and what the
            // curve factor should be.
            Taper(float curveFactor, float min = 0.0f, float max = 1.0f);

            // Specify `Type::Log` or `Type::Exp` along with minimum and maximum
            // expected values.
            Taper(Type type, float min = 0.0f, float max = 1.0f);

            // Specify the expected input range and what the curve factor should
            // be.
            Taper(float curveFactor, Range::Range<float> inputRange);

            // Specify `Type::Log` or `Type::Exp` along with expected input
            // range.
            Taper(Type type, Range::Range<float> inputRange);

            // Apply the taper to the given `value`.
            float apply(float value) const;

            // Set the curve factor to use.
            // Values below `0.5` will be exponential and values above `0.5`
            // will be logarithmic. Value is constrained to be between `0.01`
            // and `0.99`.
            void setCurveFactor(float value);

            // Set the expected input minimum.
            inline void setInputMin(float value) { inputRange.setStart(value); }

            // Set the expected input maximum.
            inline void setInputMax(float value) { inputRange.setStop(value); }

            // Set the expected input range.
            inline void setInputRange(Range::Range<float> range)
            {
                inputRange = range;
            }

            // Set the expected input range.
            inline void setInputRange(float min, float max)
            {
                inputRange = Range::Range<float>(min, max);
            }

            inline Range::Range<float> getInputRange() const
            {
                return inputRange;
            }

            inline float getCurveFactor() const { return curveFactor; }

          private:

            Range::Range<float> taperRange = Range::Range<float>(0.0f, 1.0f);
            Range::Range<float> inputRange;
            float curveFactor = 0.5f;
            float b = 0.0f;
            float c = 0.0f;

            void init(
                float curveFactor = 0.5f, float min = 0.0f, float max = 1.0f
            );

            void calcCoeffs();

            inline float calcTaperedValue(float value) const
            {
                return b * (exp(c * value) - 1);
            }
        };
    } // namespace Taper
} // namespace AudioUtilities