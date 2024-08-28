#include "Scale.h"

float AudioUtilities::Scale::scale(
    float value, float oldMin, float oldMax, float newMin, float newMax
)
{
    return scale(
        value,
        Range::Range<float>(oldMin, oldMax),
        Range::Range<float>(newMin, newMax)
    );
}

float AudioUtilities::Scale::scale(
    float value, Range::Range<float> oldRange, Range::Range<float> newRange
)
{
    return (((value - oldRange.getStart()) * newRange.getDelta())
            / oldRange.getDelta())
           + newRange.getStart();
}
