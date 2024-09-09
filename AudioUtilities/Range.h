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

            Range();

            Range(T start, T stop);

            bool operator==(const Range& other) const;

            void setBounds(T start, T stop);

            void setStart(T val);

            void setStop(T val);

            T getStart() const;

            T getStop() const;

            // Returns the lower of `start` and `stop`
            T getLower() const;

            // Returns the higher of `start` and `stop`
            T getUpper() const;

            // Returns the difference between `stop` and `start`.
            T getDelta() const;

            // Returns the absolute value of the delta
            T getAbsDelta() const;

            // Swaps the `start` and `stop` values of this instance.
            void reverse();

            // Returns a new `Range` with opposite `start` and `stop` values.
            Range getReversed() const;

            // Returns `true` if `start` is greater than `stop`.
            bool isNegative() const;

            // Returns the size of each step if this range were divided into
            // `numSteps`.
            float getStepSize(int numSteps);

            // Returns the number of steps required to get from `start` to
            // `stop` with `stepSize`.
            int getNumSteps(float stepSize);

            /*
            Returns `true` if `value` is within this range.

            `boundsInclusion` sets how the range's endpoints are considered when checking
            `value`.

            -Both: Checks inclusive of `start` and `stop`.
            -None: Checks exclusive of `start` and `stop`.
            -Start: Checks inclusive of `start`, but exclusive of `stop`.
            -Stop: Checks inclusive of `stop`, but exclusive of `start`.
            -Lower: Checks inclusive of whichever of `start` or `stop` is the
            lowest value.
            -Upper: Checks inclusive of whichever of `start` or
            `stop` is the highest value.
            */
            bool contains(float val, Inclusion boundsInclusion = Inclusion::Both);

          private:

            T start;
            T lower;
            T stop;
            T upper;
            T delta;

            void calcDelta();

            // Sets `upper` and `lower` to appropriate `start`/`stop` values.
            void parseLowerUpper();

            // Whether `value` is in this range, inclusive of bounds.
            bool inclusion(float val);

            // Whether `value` is in this range, inclusive of lower bound only.
            bool lowerInclusion(float val);

            // Whether `value` is in this range, inclusive of upper bound only.
            bool upperInclusion(float val);

            // Whether `value` is in this range, exclusive of bounds.
            bool noInclusion(float val);
        };
    } // namespace Range
} // namespace AudioUtilities