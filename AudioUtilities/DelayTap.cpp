#include "DelayTap.h"

AudioUtilities::Delay::Tap::Tap(float delayRatio, bool isPrimary)
    : delayRatio(delayRatio),
      primaryTap(isPrimary)
{}

int AudioUtilities::Delay::Tap::getDelaySamples() const
{
    return delaySamples;
}

void AudioUtilities::Delay::Tap::setDelaySamples(int samples)
{
    delaySamples = samples;
}

float AudioUtilities::Delay::Tap::getDelayRatio() const
{
    return delayRatio;
}

void AudioUtilities::Delay::Tap::setDelayRatio(float val)
{
    delayRatio = Clamp::clamp(val, 0.0f, 1.0f);
}

void AudioUtilities::Delay::Tap::setMaxIndex(int val)
{
    index.setMax(val);
    staticIndex.setMax(val);
}

void AudioUtilities::Delay::Tap::setIndex(int val)
{
    index.setIndex(val);
    staticIndex.setIndex(val);
}

void AudioUtilities::Delay::Tap::increment()
{
    // This could cause an issue if index is set not to autoIncrement.
    // staticIndex should always autoIncrement
    index += readSpeed;
    staticIndex += 1;
}

bool AudioUtilities::Delay::Tap::isPrimary() const
{
    return primaryTap;
}

const AudioUtilities::Buffer::BufferIndex& AudioUtilities::Delay::Tap::getStaticIndex()
{
    return staticIndex;
}

void AudioUtilities::Delay::Tap::incrementStaticIndex()
{
    ++staticIndex;
}
