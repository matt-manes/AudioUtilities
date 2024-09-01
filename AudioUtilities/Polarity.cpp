#include "Polarity.h"

float AudioUtilities::Polarity::bipolarToUnipolar(float val)
{
    return Clamp::clamp((val + 1.0f) * 0.5f, 0.0f, 1.0f);
}

float AudioUtilities::Polarity::unipolarToBipolar(float val)
{
    return Clamp::clamp((val * 2.0f) - 1.0f, -1.0f, 1.0f);
}
