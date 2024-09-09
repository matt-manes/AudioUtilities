#include "DelayBuffer.h"

AudioUtilities::Delay::DelayBuffer::DelayBuffer(float delayMilliseconds, int sampleRate)
    : BlendableCircleBuffer(),
      sampleRate(sampleRate)
{
    Tap tap(1.0f, true);
    taps.push_back(tap);
    setDelayMilliseconds(delayMilliseconds);
}

void AudioUtilities::Delay::DelayBuffer::write(float val)
{
    data[writedex++.getLower()] = addFeedback(val);
}

float AudioUtilities::Delay::DelayBuffer::read()
{
    float val = 0.0f;
    float output = 0.0f;
    float tapFeedback = 0.0f;
    float staticVal = 0.0f;
    float combinedFeedback = 0.0f;
    for (int i = 0; i < taps.size(); ++i)
    {
        // Read tap with vari-speed index.
        val = BlendableCircleBuffer::read(taps[i].index) * taps[i].gain;
        // Read tap with static speed index.
        staticVal = BlendableCircleBuffer::read(taps[i].getStaticIndex()) * taps[i].gain;
        // Determine which is going to serve as the feedback value for the tap.
        switch (taps[i].feedback.type)
        {
            case Normal: tapFeedback = val; break;
            case Static: tapFeedback = staticVal;
        }
        taps[i].feedback.write(tapFeedback);
        combinedFeedback += tapFeedback;
        output += val;
        incrementTap(taps[i]);
    }
    feedback.write(combinedFeedback / taps.size());
    return output / taps.size();
}

float AudioUtilities::Delay::DelayBuffer::addFeedback(float val)
{
    if (feedback.type == Normal || feedback.type == Static)
    {
        if (feedback.source == Combined)
        {
            return val + feedback.read();
        }
        else if (feedback.source == PerTap)
        {
            return val + readPerTapFeedback();
        }
    }
}

int AudioUtilities::Delay::DelayBuffer::getSampleRate() const
{
    return sampleRate;
}

void AudioUtilities::Delay::DelayBuffer::setSampleRate(int rate)
{
    sampleRate = rate;
    setDelayMilliseconds(delayMilliseconds);
}

float AudioUtilities::Delay::DelayBuffer::getDelayMilliseconds() const
{
    return delayMilliseconds;
}

// Set the new delay time and configure taps for it.
void AudioUtilities::Delay::DelayBuffer::setDelayMilliseconds(float ms)
{
    delayMilliseconds = ms;
    delaySamples = SampleRate::fromMilliseconds(delayMilliseconds, sampleRate);
    delaySamples = std::max(delaySamples, 1);
    // 2x samples b/c pretending 1 buffer is 2
    resize(2 * delaySamples);
}

void AudioUtilities::Delay::DelayBuffer::setReadSpeed(float speed, int tapNum)
{
    if (tapNum < 0)
    {
        for (int i = 0; i < taps.size(); ++i)
        {
            taps[i].readSpeed = speed;
        }
        return;
    }
    taps[tapNum].readSpeed = speed;
}

float AudioUtilities::Delay::DelayBuffer::getReadSpeed(int tapNum)
{
    return taps[tapNum].readSpeed;
}

AudioUtilities::Delay::Tap& AudioUtilities::Delay::DelayBuffer::tap(int index)
{
    return taps[index];
}

void AudioUtilities::Delay::DelayBuffer::addTap(float delayRatio)
{
    Tap tap(delayRatio);
    configureTap(tap);
    taps.push_back(tap);
}

void AudioUtilities::Delay::DelayBuffer::removeTap(int index)
{
    // Can't remove only or primary tap
    if (taps.size() == 1 || taps[index].isPrimary())
    {
        return;
    }
    taps.erase(taps.begin() + index);
}

float AudioUtilities::Delay::DelayBuffer::readPerTapFeedback()
{
    float output = 0.0f;
    for (int i = 0; i < taps.size(); ++i)
    {
        output += taps[i].feedback.read();
    }
    return output / taps.size();
}

int AudioUtilities::Delay::DelayBuffer::getNumTaps()
{
    return taps.size();
}

float AudioUtilities::Delay::DelayBuffer::getFeedbackGain(int tapNum)
{
    if (tapNum < 0)
    {
        return feedback.gain;
    }
    return taps[tapNum].feedback.gain;
}

void AudioUtilities::Delay::DelayBuffer::setFeedbackGain(float val, int tapNum)
{
    if (tapNum < 0)
    {
        feedback.gain = val;
        return;
    }
    taps[tapNum].feedback.gain = val;
}

AudioUtilities::Delay::FeedbackType AudioUtilities::Delay::DelayBuffer::getFeedbackType(
    int tapNum
)
{
    return taps[tapNum].feedback.type;
}

void AudioUtilities::Delay::DelayBuffer::setFeedbackType(FeedbackType type, int tapNum)
{
    if (tapNum < 0)
    {
        for (int i = 0; i < taps.size(); ++i)
        {
            taps[i].feedback.type = type;
        }
        return;
    }
    taps[tapNum].feedback.type = type;
}

AudioUtilities::Delay::FeedbackSource AudioUtilities::Delay::DelayBuffer::
    getFeedbackSource()
{
    return feedback.source;
}

void AudioUtilities::Delay::DelayBuffer::setFeedbackSource(FeedbackSource source)
{
    feedback.source = source;
}

void AudioUtilities::Delay::DelayBuffer::incrementTap(Tap& tap)
{
    if (tap.index.autoIncrement)
    {
        tap.increment();
    }
    else
    {
        tap.incrementStaticIndex();
    }
}

void AudioUtilities::Delay::DelayBuffer::resize(int size)
{
    BlendableCircleBuffer::resize(size);
    configureTaps();
}

void AudioUtilities::Delay::DelayBuffer::configureTap(Tap& tap)
{
    int buffSize = size();
    // Buffer is 2x the size of max delay
    int delaySamples = buffSize * 0.5f * tap.getDelayRatio();
    tap.setDelaySamples(delaySamples);
    tap.setMaxIndex(buffSize - 1);
    // Higher indicies will wrap and hit the written data sooner
    // tap->index = writedex.getFull() - delaySamples + 1;
    // tap->staticIndex = writedex.getFull() - delaySamples + 1;
    tap.setIndex(writedex.getFull() - delaySamples + 1);
}

void AudioUtilities::Delay::DelayBuffer::configureTaps()
{
    for (int i = 0; i < taps.size(); ++i)
    {
        configureTap(taps[i]);
    }
}
