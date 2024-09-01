#include "Blend.h"

float AudioUtilities::Blend::blend(float val1, float val2, float control)
{
    return val1 + (Clamp::clamp(control, 0.0f, 1.0f) * (val2 - val1));
}

float AudioUtilities::Blend::bipolarBlend(float val1, float val2, float control)
{
    return blend(val1, val2, Polarity::bipolarToUnipolar(control));
}