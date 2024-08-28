#include "Fade.h"
#include "SampleRate.h"

AudioUtilities::Fade::Fade::Fade(
    float lengthMilliseconds,
    int sampleRate,
    Direction direction,
    float curveFactor
)
    : Ramp::Ramp(lengthMilliseconds, sampleRate, 0.0f, 1.0f, curveFactor)
{
    setDirection(direction);
}

AudioUtilities::Fade::Fade::Fade(
    int lengthSamples, int sampleRate, Direction direction, float curveFactor
)
    : Ramp::Ramp(lengthSamples, sampleRate, 0.0f, 1.0f, curveFactor)
{
    setDirection(direction);
}

void AudioUtilities::Fade::Fade::setDirection(Direction direction)
{
    this->direction = direction;
    if (direction == Direction::In) { range.setBounds(0.0f, 1.0f); }
    else { range.setBounds(1.0f, 0.0f); }
    currentVal = getStart();
    calculateStepSize();
}
