#include "Taper.h"

AudioUtilities::Taper::Taper::Taper()
{
    init(0.5f, 0.0f, 1.0f);
}

AudioUtilities::Taper::Taper::Taper(float curveFactor, float min, float max)
{
    init(curveFactor, min, max);
}

AudioUtilities::Taper::Taper::Taper(Type type, float min, float max)
{
    float curveFactor = 0.5f;
    if (type == Type::Log)
    {
        curveFactor = 0.9f;
    }
    else if (type == Type::Exp)
    {
        curveFactor = 0.1f;
    }
    init(curveFactor, min, max);
}

AudioUtilities::Taper::Taper::Taper(float curveFactor, Range::Range<float> inputRange)
{
    init(curveFactor, inputRange.getStart(), inputRange.getStop());
}

AudioUtilities::Taper::Taper::Taper(Type type, Range::Range<float> inputRange)
{
    float curveFactor = 0.5f;
    if (type == Type::Log)
    {
        curveFactor = 0.9f;
    }
    else if (type == Type::Exp)
    {
        curveFactor = 0.1f;
    }
    init(curveFactor, inputRange.getStart(), inputRange.getStop());
}

void AudioUtilities::Taper::Taper::init(float curveFactor, float min, float max)
{
    this->curveFactor = Clamp::clamp(curveFactor, 0.01f, 0.99f);
    inputRange = Range::Range<float>(min, max);
    calcCoeffs();
}

float AudioUtilities::Taper::Taper::apply(float val)
{
    // If `curveFactor` is in this range, we're considering it linear so as to avoid
    // dividing by 0 or almost 0.
    if (linearRange.contains(curveFactor))
    {
        return val;
    }

    // No need to scale back and forth if input is same as taper
    if (taperRange == inputRange)
    {
        return calcTaperedValue(val);
    }

    float scaledValue = Scale::scale(val, inputRange, taperRange);
    float scaledOutput = calcTaperedValue(scaledValue);
    return Clamp::clamp(Scale::scale(scaledOutput, taperRange, inputRange), inputRange);
}

void AudioUtilities::Taper::Taper::setCurveFactor(float val)
{
    curveFactor = Clamp::clamp(val, 0.01f, 0.99f);
    calcCoeffs();
}

void AudioUtilities::Taper::Taper::setInputMin(float val)
{
    inputRange.setStart(val);
}

void AudioUtilities::Taper::Taper::setInputMax(float val)
{
    inputRange.setStop(val);
}

void AudioUtilities::Taper::Taper::setInputRange(Range::Range<float> range)
{
    inputRange = range;
}

void AudioUtilities::Taper::Taper::setInputRange(float min, float max)
{
    inputRange = Range::Range<float>(min, max);
}

AudioUtilities::Range::Range<float> AudioUtilities::Taper::Taper::getInputRange() const
{
    return inputRange;
}

float AudioUtilities::Taper::Taper::getCurveFactor() const
{
    return curveFactor;
}

void AudioUtilities::Taper::Taper::calcCoeffs()
{
    // `curveFactor` of `0.5f` will cause a divide by 0
    if (curveFactor == 0.5f)
    {
        return;
    }
    float min = taperRange.getStart();
    float max = taperRange.getStop();
    float bDenominator = min - (2 * curveFactor) + max;
    float diff = curveFactor - min;
    b = (diff * diff) / bDenominator;
    c = 2 * log((max - curveFactor) / diff);
}

float AudioUtilities::Taper::Taper::calcTaperedValue(float val) const
{
    return b * (exp(c * val) - 1);
}
