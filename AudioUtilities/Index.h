#pragma once

#include "Range.h"
#include <cmath>

namespace AudioUtilities
{
    namespace Index
    {
        /*
        Auto-wrapping index that can have a decimal component.

        Index bounds are clamped to 0 and above.

        If you try to make the minimum index less than the max,
        they will be automatically swapped, and vice versa.

        Use `getLower()`, `getUpper()`, and `getDecimal()` along with an
        interpolator to get container values between indicies.

        e.g. `float value = Blend::blend(data[index.getLower()],
        data[index.getUpper()], index.getDecimal())
        */
        class Index
        {
          public:

            Index() { setBounds(0, 1); }

            // Initialize with a maximum index.
            Index(int maxIndex) { setBounds(0, maxIndex); }

            // Initialize with minimum and maximum indicies.
            Index(int minIndex, int maxIndex) { setBounds(minIndex, maxIndex); }

            // Initialize with `Range` instance
            Index(Range::Range<int> bounds) { setBounds(bounds); }

            Index &operator++();
            Index operator++(int);
            Index &operator--();
            Index operator--(int);

            Index &operator=(float val);
            Index &operator+(float val);
            Index &operator-(float val);
            Index &operator*(float val);
            Index &operator/(float val);

            Index &operator+=(float val);
            Index &operator-=(float val);
            Index &operator*=(float val);
            Index &operator/=(float val);

            // Set the minimum index.
            void setMin(int val);

            // Set the maximum index.
            void setMax(int val);

            // Set the minimum and maximum indicies.
            void setBounds(int min, int max);

            // Set the minimum and maximum indicies.
            void setBounds(Range::Range<int> bounds);

            // Returns the start and stop indicies
            Range::Range<int> getBounds() { return bounds; }

            // Sets index to the given value, wrapping if neccessary.
            void setIndex(float val);

            // Returns the current floating point index.
            inline float getFull() const { return full; }

            // Returns the smallest integer in the indexing range that is larger
            // than `full`.
            // If `full` is between `max` and `paddedMax`, `upper` will be
            // equal to the minimum index.
            inline int getUpper() const { return upper; }

            // Returns the largest integer in the indexing range that is less
            // than `full`.
            inline int getLower() const { return lower; }

            // Returns the decimal portion of the index.
            inline float getDecimal() const { return decimal; }

            // Returns the minimum index
            inline int getMin() const { return bounds.getStart(); }

            // Returns the maximum index
            inline int getMax() const { return bounds.getStop(); }

          private:

            float full = 0.0f;
            float decimal;
            int upper, lower;
            Range::Range<int> bounds;

            // padded ranges are used so that the decimal component can be
            // between the max and min.
            Range::Range<int> paddedZone, paddedBounds;

            inline int getPaddedMax() { return paddedBounds.getStop(); }

            // Wraps index to be between the minimum and padded max, inclusive
            // of `min`.
            void wrap();

            // Returns `true` if index is not between minimum index and
            // padded max, inclusive of minimum.
            inline bool isOutOfBounds()
            {
                return !(paddedBounds.contains(full, Range::Inclusion::Start));
            };

            // Checks if `full` is between max and padded max.
            inline bool isInPaddedZone()
            {
                return paddedZone.contains(full, Range::Inclusion::None);
            }

            // Uses current value of `full` to set `lower`, `upper`, and
            // `decimal` members.
            void splitIndex();

            // Set negative values to 0 and ensure `start` is less than `stop`.
            Range::Range<int> enforceBoundsConstraints(Range::Range<int> bounds
            );
        };

    } // namespace Index
} // namespace AudioUtilities