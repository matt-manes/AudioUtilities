#include "Ramp.h"

AudioUtilities::Ramp::Ramp::Ramp()
    : lengthSamples(1),
      sampleRate(1),
      curve(0.5f, 0.0f, 1.0f),
      currentVal(range.getStart())
{
    calculateStepSize();
}

AudioUtilities::Ramp::Ramp::Ramp(
    float lengthMilliseconds,
    int sampleRate,
    float startVal,
    float stopVal,
    float curveFactor
)
    : lengthSamples(SampleRate::fromMilliseconds(lengthMilliseconds, sampleRate)),
      sampleRate(sampleRate),
      curve(curveFactor, startVal, stopVal),
      currentVal(startVal)
{
    range.setBounds(startVal, stopVal);
    calculateStepSize();
}

AudioUtilities::Ramp::Ramp::Ramp(
    int lengthSamples, int sampleRate, float startVal, float stopVal, float curveFactor
)
    : lengthSamples(lengthSamples),
      sampleRate(sampleRate),
      curve(curveFactor, startVal, stopVal),
      currentVal(startVal)
{
    range.setBounds(startVal, stopVal);
    calculateStepSize();
}

void AudioUtilities::Ramp::Ramp::tick()
{
    if (!active)
    {
        return;
    }
    incrementCurrentVal();
    // Nesting these to minimize cycles spent comparing `currentVal` to `stopVal`.
    if (active && !finished)
    {
        if (stopValueReached())
        {
            clampCurrentVal();
            if (bidirectional)
            {
                reverse();
            }
            if (freeRunning)
            {
                reset();
            }
            else
            {
                active = false;
                finished = true;
            }
        }
    }
}

float AudioUtilities::Ramp::Ramp::getNext()
{
    tick();
    return read();
}

void AudioUtilities::Ramp::Ramp::start()
{
    active = true;
}

void AudioUtilities::Ramp::Ramp::stop()
{
    active = false;
}

void AudioUtilities::Ramp::Ramp::reset()
{
    currentVal = range.getStart();
    finished = false;
}

bool AudioUtilities::Ramp::Ramp::isFinished() const
{
    return finished;
}

bool AudioUtilities::Ramp::Ramp::isActive() const
{
    return active;
}

bool AudioUtilities::Ramp::Ramp::isReverse() const
{
    return range.isNegative();
}

float AudioUtilities::Ramp::Ramp::getStepSize() const
{
    return stepSize;
}

float AudioUtilities::Ramp::Ramp::read()
{
    return curve.apply(currentVal);
}

float AudioUtilities::Ramp::Ramp::getStart() const
{
    return range.getStart();
}

void AudioUtilities::Ramp::Ramp::setStart(float value)
{
    range.setStart(value);
    calculateStepSize();
}

float AudioUtilities::Ramp::Ramp::getStop() const
{
    return range.getStop();
}

void AudioUtilities::Ramp::Ramp::setStop(float value)
{
    range.setStop(value);
    calculateStepSize();
}

float AudioUtilities::Ramp::Ramp::getCurve()
{
    return curve.getCurveFactor();
}

void AudioUtilities::Ramp::Ramp::setCurve(float val)
{
    curve.setCurveFactor(val);
}

int AudioUtilities::Ramp::Ramp::getLengthSamples() const
{
    return lengthSamples;
}

void AudioUtilities::Ramp::Ramp::setLengthSamples(int samples)
{
    lengthSamples = samples;
    calculateStepSize();
}

void AudioUtilities::Ramp::Ramp::setLengthMilliseconds(float milliseconds)
{
    setLengthSamples(SampleRate::fromMilliseconds(milliseconds, sampleRate));
}

void AudioUtilities::Ramp::Ramp::setLengthSteps(int numSteps)
{
    // Could just use `setLengthSamples()` instead, but `setLengthSteps()` is more
    // intuitive naming.
    setLengthSamples(numSteps);
}

void AudioUtilities::Ramp::Ramp::reverse()
{
    range.reverse();
    calculateStepSize();
}

void AudioUtilities::Ramp::Ramp::calculateStepSize()
{
    stepSize = range.getStepSize(lengthSamples);
}

void AudioUtilities::Ramp::Ramp::clampCurrentVal()
{
    currentVal = Clamp::clamp(currentVal, range);
}

void AudioUtilities::Ramp::Ramp::incrementCurrentVal()
{
    currentVal += stepSize;
}

bool AudioUtilities::Ramp::Ramp::stopValueReached() const
{
    if (isReverse())
    {
        return currentVal <= getStop();
    }
    return currentVal >= getStop();
}