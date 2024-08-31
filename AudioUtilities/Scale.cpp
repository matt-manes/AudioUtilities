#include "Scale.h"

float AudioUtilities::Scale::scale(
    float val, float oldMin, float oldMax, float newMin, float newMax
)
{
    return scale(
        val,
        Range::Range<float>(oldMin, oldMax),
        Range::Range<float>(newMin, newMax)
    );
}

float AudioUtilities::Scale::scale(
    float val, Range::Range<float> oldRange, Range::Range<float> newRange
)
{
    return (((val - oldRange.getStart()) * newRange.getDelta())
            / oldRange.getDelta())
           + newRange.getStart();
}
