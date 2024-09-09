#include "Delay.h"

AudioUtilities::Delay::Delay::Delay(
    float delayMilliseconds, int sampleRate, BufferType bufferType
)
    : delayMilliseconds(delayMilliseconds),
      sampleRate(sampleRate),
      bufferType(bufferType)
{
    switch (bufferType)
    {
        case Circle: buffer = DelayBuffer(delayMilliseconds, sampleRate); break;
        case PingPong: buffer = PingPongDelayBuffer(delayMilliseconds, sampleRate);
    }
}

void AudioUtilities::Delay::Delay::write(float val)
{
    buffer.write(val);
}

float AudioUtilities::Delay::Delay::read()
{
    return buffer.read();
}

float AudioUtilities::Delay::Delay::process(float input, float blend)
{
    blend = Clamp::clamp(blend, 0.0f, 1.0f);
    return __process(input, blend);
}

float AudioUtilities::Delay::Delay::process(float input)
{
    return __process(input, blend);
}

float AudioUtilities::Delay::Delay::getBlend()
{
    return blend;
}

void AudioUtilities::Delay::Delay::setBlend(float val)
{
    blend = Clamp::clamp(blend, 0.0f, 1.0f);
}

int AudioUtilities::Delay::Delay::getSampleRate()
{
    return sampleRate;
}

void AudioUtilities::Delay::Delay::setSampleRate(int val)
{
    sampleRate = val;
    buffer.setSampleRate(val);
}

float AudioUtilities::Delay::Delay::getDelayMilliseconds()
{
    return delayMilliseconds;
}

void AudioUtilities::Delay::Delay::setDelayMilliseconds(float val)
{
    delayMilliseconds = val;
    buffer.setDelayMilliseconds(val);
}

AudioUtilities::Delay::BufferType AudioUtilities::Delay::Delay::getBufferType()
{
    return bufferType;
}

float AudioUtilities::Delay::Delay::__process(float input, float blend)
{
    write(input);
    return Blend::blend(input, read(), blend);
}

//========================================================================================
//========================================================================================
//========================================================================================

AudioUtilities::Delay::MultiChannelDelay::MultiChannelDelay(
    int numChannels, float delayMilliseconds, int sampleRate, BufferType bufferType
)
{
    this->sampleRate = sampleRate;
    for (int i = 0; i < numChannels; ++i)
    {
        channels.push_back(Delay(delayMilliseconds, sampleRate, bufferType));
    }
}

AudioUtilities::Delay::MultiChannelDelay::MultiChannelDelay(std::vector<Delay> &channels)
{
    // Assumes they are all set to the same sample rate.
    this->sampleRate = channels[0].getSampleRate();
    channels = channels;
}

void AudioUtilities::Delay::MultiChannelDelay::setSampleRate(int rate)
{
    sampleRate = rate;
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].setSampleRate(rate);
    }
}

int AudioUtilities::Delay::MultiChannelDelay::getSampleRate()
{
    return sampleRate;
}

void AudioUtilities::Delay::MultiChannelDelay::setDelayMilliseconds(float ms)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].setDelayMilliseconds(ms);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::setReadSpeed(float speed)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].buffer.setReadSpeed(speed);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::setReadSpeed(float speed, int tapNum)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].buffer.setReadSpeed(speed, tapNum);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::addTap(float delayRatio)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].buffer.addTap(delayRatio);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::removeTap(int index)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].buffer.removeTap(index);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::setFeedbackGain(float val)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].buffer.setFeedbackGain(val);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::setBlend(float val)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].setBlend(val);
    }
}

void AudioUtilities::Delay::MultiChannelDelay::setFeedbackType(FeedbackType feedbackType)
{
    for (int i = 0; i < channels.size(); ++i)
    {
        channels[i].buffer.setFeedbackType(feedbackType);
    }
}
