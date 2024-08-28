#include "Ramp.h"
#include "Clamp.h"
#include "SampleRate.h"

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
    : lengthSamples(SampleRate::fromMilliseconds(lengthMilliseconds, sampleRate)
      ),
      sampleRate(sampleRate),
      curve(curveFactor, startVal, stopVal),
      currentVal(startVal)
{
    range.setBounds(startVal, stopVal);
    calculateStepSize();
}

AudioUtilities::Ramp::Ramp::Ramp(
    int lengthSamples,
    int sampleRate,
    float startVal,
    float stopVal,
    float curveFactor
)
    : lengthSamples(lengthSamples),
      sampleRate(sampleRate),
      curve(curveFactor, startVal, stopVal),
      currentVal(startVal)
{
    range.setBounds(startVal, stopVal);
    calculateStepSize();
}

void AudioUtilities::Ramp::Ramp::incrementCurrentVal()
{
    currentVal += stepSize;
}

void AudioUtilities::Ramp::Ramp::tick()
{
    if (!active) { return; }
    incrementCurrentVal();
    // Nesting these to minimize cycles spent comparing `currentVal`
    // to `stopVal`.
    if (active && !finished)
    {
        if (stopValueReached())
        {
            clampCurrentVal();
            active = false;
            finished = true;
        }
    }
}

void AudioUtilities::Ramp::Ramp::reset()
{
    currentVal = range.getStart();
    finished = false;
}

void AudioUtilities::Ramp::Ramp::setStart(float value)
{
    range.setStart(value);
    calculateStepSize();
}

void AudioUtilities::Ramp::Ramp::setStop(float value)
{
    range.setStop(value);
    calculateStepSize();
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

void AudioUtilities::Ramp::Ramp::reverse()
{
    range.reverse();
    calculateStepSize();
}

void AudioUtilities::Ramp::Ramp::clampCurrentVal()
{
    if (isReverse())
    {
        currentVal = Clamp::clamp(currentVal, getStop(), getStart());
    }
    else { currentVal = Clamp::clamp(currentVal, getStart(), getStop()); }
}

bool AudioUtilities::Ramp::Ramp::stopValueReached() const
{
    if (isReverse()) { return currentVal <= getStop(); }
    return currentVal >= getStop();
}