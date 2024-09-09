#include "PingPongBuffer.h"

void AudioUtilities::Delay::PingPongDelayBuffer::write(float val)
{
    Buffer::BufferIndex prev = writedex;
    writeData[writedex++.getLower()] = addFeedback(val);
    // If writedex wraps around, set swap flag.
    if (writedex.getLower() < prev.getLower())
    {
        shouldSwap = true;
    }
}

float AudioUtilities::Delay::PingPongDelayBuffer::read()
{
    float val = 0.0f;
    float output = 0.0f;
    float tapFeedback = 0.0f;
    float staticVal = 0.0f;
    float combinedFeedback = 0.0f;
    for (int i = 0; i < taps.size(); ++i)
    {
        // Read tap with vari-speed index.
        val = read(taps[i].index) * taps[i].gain;
        // Read tap with static speed index.
        staticVal = read(taps[i].getStaticIndex()) * taps[i].gain;
        // Determine which is going to serve as the feedback value for the tap.
        switch (taps[i].feedback.type)
        {
            case Normal: tapFeedback = val;
            case Static: tapFeedback = staticVal;
        }
        taps[i].feedback.write(tapFeedback);
        combinedFeedback += tapFeedback;
        output += val;
        incrementTap(taps[i]);
    }
    feedback.write(combinedFeedback / taps.size());
    if (shouldSwap == true)
    {
        writeData.swap(readData);
        shouldSwap = false;
    }
    return output / taps.size();
}

float AudioUtilities::Delay::PingPongDelayBuffer::read(Index::Index index)
{
    return Blend::blend(
        readData[index.getLower()], readData[index.getUpper()], index.getDecimal()
    );
}

void AudioUtilities::Delay::PingPongDelayBuffer::setDelayMilliseconds(float ms)
{
    delayMilliseconds = ms;
    delaySamples = SampleRate::fromMilliseconds(delayMilliseconds, sampleRate);
    resize(delaySamples);
}

void AudioUtilities::Delay::PingPongDelayBuffer::flush()
{
    writeData.assign(writeData.size(), 0.0f);
    readData.assign(readData.size(), 0.0f);
}

void AudioUtilities::Delay::PingPongDelayBuffer::configureTap(Tap& tap)
{
    int buffSize = size();
    int delaySamples = buffSize * tap.getDelayRatio();
    tap.setDelaySamples(delaySamples);
    tap.setMaxIndex(buffSize - 1);
    // Higher indicies will wrap and hit the written data sooner
    tap.setIndex(writedex.getFull() - delaySamples + 1);
}

void AudioUtilities::Delay::PingPongDelayBuffer::resize(int size)
{
    readData.resize(size);
    DelayBuffer::resize(size);
}
