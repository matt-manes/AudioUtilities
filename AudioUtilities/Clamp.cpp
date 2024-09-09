#include "Clamp.h"

float AudioUtilities::Clamp::clamp(float val, Range::Range<float> range)
{
    if (range.contains(val))
    {
        return val;
    }

    // By using absolute value of deltas we account for min value being greater than max
    float startDelta = std::abs(val - range.getStart());
    float stopDelta = std::abs(val - range.getStop());
    // `val` is outside of range and closer to `range.start`
    if (startDelta < stopDelta)
    {
        return range.getStart();
    }
    // `val` is outside of range and closer to `range.stop`
    return range.getStop();
}

float AudioUtilities::Clamp::clamp(float val, float min, float max)
{
    Range::Range<float> range(min, max);
    return clamp(val, range);
}
