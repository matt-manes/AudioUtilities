#include "DelayLine.h"

float AudioUtilities::DelayLine::Tap::getReadSpeed() const
{
    return readSpeed;
}

void AudioUtilities::DelayLine::Tap::setReadSpeed(float val)
{
    readSpeed = val;
}

float AudioUtilities::DelayLine::Tap::getGain() const
{
    return gain;
}

void AudioUtilities::DelayLine::Tap::setGain(float val)
{
    gain = val;
}

int AudioUtilities::DelayLine::Tap::getDelaySamples() const
{
    return delaySamples;
}

void AudioUtilities::DelayLine::Tap::setDelaySamples(int samples)
{
    delaySamples = samples;
}

float AudioUtilities::DelayLine::Tap::getDelayRatio() const
{
    return delayRatio;
}

void AudioUtilities::DelayLine::Tap::setDelayRatio(float val)
{
    delayRatio = Clamp::clamp(val, 0.0f, 1.0f);
}

void AudioUtilities::DelayLine::Tap::increment()
{
    index += readSpeed;
}

bool AudioUtilities::DelayLine::Tap::isPrimary() const
{
    return primaryTap;
}

void AudioUtilities::DelayLine::Tap::setPrimary(bool primary)
{
    primaryTap = primary;
}

// =============================================================================
// =============================================================================
// =============================================================================

AudioUtilities::DelayLine::DelayLine::DelayLine(
    float delayMilliseconds, int sampleRate
)
    : CircleBuff(),
      sampleRate(sampleRate)
{
    addTap(1.0f);
    taps[0].setPrimary(true);
    setDelayMilliseconds(delayMilliseconds);
}

void AudioUtilities::DelayLine::DelayLine::write(float val)
{
    data[writedex.getLower()] = val;
    writedex += writeSpeed;
}

float AudioUtilities::DelayLine::DelayLine::read()
{
    float val = 0.0f;
    for (int i = 0; i < taps.size(); ++i)
    {
        val += (CircleBuff::read(taps[i].index) * taps[i].getGain());
        if (autoIncrement)
        {
            taps[i].increment();
        }
    }
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
}

void AudioUtilities::DelayLine::DelayLine::setReadSpeed(float speed)
{
    for (int i = 0; i < taps.size(); ++i)
    {
        taps[i].setReadSpeed(speed);
    }
}

void AudioUtilities::DelayLine::DelayLine::setReadSpeed(float speed, int tapNum)
{
    taps[tapNum].setReadSpeed(speed);
}

float AudioUtilities::DelayLine::DelayLine::getWriteSpeed() const
{
    return writeSpeed;
}

void AudioUtilities::DelayLine::DelayLine::setWriteSpeed(float speed)
{
    writeSpeed = speed;
}

AudioUtilities::DelayLine::Tap &AudioUtilities::DelayLine::DelayLine::tap(
    int index
)
{
    return taps[index];
}

void AudioUtilities::DelayLine::DelayLine::addTap(float delayRatio)
{
    Tap tap;
    tap.setDelayRatio(delayRatio);
    taps.push_back(tap);
    configureTap(taps.size() - 1);
}

void AudioUtilities::DelayLine::DelayLine::removeTap(int index)
{
    // Can't remove only or primary tap
    if (taps.size() == 1 || taps[index].isPrimary())
    {
        return;
    }
    taps.erase(taps.begin() + index);
}

int AudioUtilities::DelayLine::DelayLine::getNumTaps()
{
    return taps.size();
}

void AudioUtilities::DelayLine::DelayLine::resize(int size)
{
    CircleBuff::resize(size);
    configureTaps();
}

void AudioUtilities::DelayLine::DelayLine::configureTap(int tapNum)
{
    int buffSize = size();
    // Buffer is 2x the size of max delay
    int delaySamples = buffSize * 0.5f * taps[tapNum].getDelayRatio();
    taps[tapNum].setDelaySamples(delaySamples);
    taps[tapNum].index.setMax(buffSize - 1);
    // Higher indicies will wrap and hit the written data sooner
    taps[tapNum].index = writedex.getFull() - delaySamples + 1;
}

void AudioUtilities::DelayLine::DelayLine::configureTaps()
{
    for (int i = 0; i < taps.size(); ++i)
    {
        configureTap(i);
    }
}
