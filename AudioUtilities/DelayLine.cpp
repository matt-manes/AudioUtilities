#include "DelayLine.h"

AudioUtilities::DelayLine::DelayLine::DelayLine(
    float delayMilliseconds, int sampleRate
)
    : CircleBuff(),
      sampleRate(sampleRate)
{
    setDelayMilliseconds(delayMilliseconds);
}

float AudioUtilities::DelayLine::DelayLine::read()
{
    float val = operator[](readex);
    if (autoIncrementReadex) { incrementRead(); }
    return val;
}

int AudioUtilities::DelayLine::DelayLine::getSampleRate() const
{
    return sampleRate;
}

void AudioUtilities::DelayLine::DelayLine::setSampleRate(int rate)
{
    sampleRate = rate;
    setDelayMilliseconds(delayMilliseconds);
}

float AudioUtilities::DelayLine::DelayLine::getDelayMilliseconds() const
{
    return delayMilliseconds;
}

void AudioUtilities::DelayLine::DelayLine::setDelayMilliseconds(float ms)
{
    delayMilliseconds = ms;
    delaySamples = SampleRate::fromMilliseconds(delayMilliseconds, sampleRate);
    // 2x samples b/c pretending 1 buffer is 2
    resize(2 * delaySamples);
    // Offset read from write by delay amount
    readex = writedex.getFull() + size() * 0.5f;
}

AudioUtilities::Index::Index *AudioUtilities::DelayLine::DelayLine::getReadex()
{
    return &readex;
}

float AudioUtilities::DelayLine::DelayLine::getReadSpeed() const
{
    return readSpeed;
}

void AudioUtilities::DelayLine::DelayLine::setReadSpeed(float speed)
{
    readSpeed = speed;
}

void AudioUtilities::DelayLine::DelayLine::resize(int size)
{
    CircleBuff::resize(size);
    readex.setMax(size - 1);
}

void AudioUtilities::DelayLine::DelayLine::incrementRead()
{
    readex += readSpeed;
}
