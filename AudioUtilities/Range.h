#pragma once

#include <cmath>

namespace AudioUtilities
{
    namespace Range
    {
        // For use with `Range::contains()`.
        enum Inclusion
        {
            Both,
            None,
            Start,
            Stop,
            Lower,
            Upper
        };

        /*
        Represents a number range between `start` and `stop`.
        */
        template <class T> class Range
        {
          public:

            Range() { setBounds((T)0, (T)1); };

            Range(T start, T stop) { setBounds(start, stop); }

            inline bool operator==(const Range &other) const
            {
                return (start == other.start) && (stop == other.stop);
            }

            inline void setBounds(T start, T stop)
            {
                this->start = start;
                this->stop = stop;
                parseLowerUpper();
                calcDelta();
            }

            inline void setStart(T value)
            {
                start = value;
                parseLowerUpper();
                calcDelta();
            }

            inline void setStop(T value)
            {
                stop = value;
                parseLowerUpper();
                calcDelta();
            }

            inline T getStart() const { return start; }

            inline T getStop() const { return stop; }

            // Returns the difference between `stop` and `start`.
            inline T getDelta() const { return delta; }

            // Swaps the `start` and `stop` values of this instance.
            inline void reverse()
            {
                float tmp = start;
                start = stop;
                stop = tmp;
                parseLowerUpper();
                calcDelta();
            }

            // Returns a new `Range` with opposite `start` and `stop` values.
            inline Range getReversed() const { return Range(stop, start); }

            // Returns `true` if `start` is greater than `stop`.
            inline bool isNegative() const { return delta < 0.0f; }

            // Returns the size of each step if this range were divided into
            // `numSteps`.
            inline float getStepSize(int numSteps) { return delta / numSteps; }

            // Returns the number of steps required to get from `start` to
            // `stop` with `stepSize`.
            inline int getNumSteps(float stepSize)
            {
                return std::abs((int)std::ceil(delta / stepSize));
            }

            /*
            Returns `true` if `value` is within this range.

            `boundsInclusion` sets how the range's endpoints are considered when
            checking `value`.

            -Both: Checks inclusive of `start` and `stop`.
            -None: Checks exclusive of `start` and `stop`.
            -Start: Checks inclusive of `start`, but exclusive of `stop`.
            -Stop: Checks inclusive of `stop`, but exclusive of `start`.
            -Lower: Checks inclusive of whichever of `start` or `stop` is the
            lowest value.
            -Upper: Checks inclusive of whichever of `start` or
            `stop` is the highest value.
            */
            inline bool contains(
                float value, Inclusion boundsInclusion = Inclusion::Both
            )
            {
                switch (boundsInclusion)
                {
                    case Both: return inclusion(value);
                    case None: return noInclusion(value);
                    case Lower: return lowerInclusion(value);
                    case Upper: return upperInclusion(value);
                    case Start:
                    {
                        if (isNegative()) { return upperInclusion(value); }
                        return lowerInclusion(value);
                    }
                    case Stop:
                    {
                        if (isNegative()) { return lowerInclusion(value); }
                        return upperInclusion(value);
                    }
                }
            }

          private:

            T start;
            T lower;
            T stop;
            T upper;
            T delta;

            inline void calcDelta() { delta = stop - start; }

            // Sets `upper` and `lower` to appropriate `start`/`stop` values.
            inline void parseLowerUpper()
            {
                if (start < stop)
                {
                    lower = start;
                    upper = stop;
                }
                else
                {
                    lower = stop;
                    upper = start;
                }
            }

            // Whether `value` is in this range, inclusive of bounds.
            bool inclusion(float value)
            {
                return (lower <= value) && (value <= upper);
            }

            // Whether `value` is in this range, inclusive of lower bound only.
            bool lowerInclusion(float value)
            {
                return (lower <= value) && (value < upper);
            }

            // Whether `value` is in this range, inclusive of upper bound only.
            bool upperInclusion(float value)
            {
                return (lower < value) && (value <= upper);
            }

            // Whether `value` is in this range, exclusive of bounds.
            bool noInclusion(float value)
            {
                return (lower < value) && (value < upper);
            }
        };
    } // namespace Range
} // namespace AudioUtilities