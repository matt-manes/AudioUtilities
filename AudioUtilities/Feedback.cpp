#include "Feedback.h"

void AudioUtilities::Delay::FeedbackSample::write(float val)
{
    sample = val;
}

float AudioUtilities::Delay::FeedbackSample::read()
{
    return sample * gain;
}
