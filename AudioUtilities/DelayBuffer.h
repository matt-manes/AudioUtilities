#pragma once

#include "CircleBuffer.h"
#include "SampleRate.h"
#include "Blend.h"
#include "Feedback.h"
#include "DelayTap.h"
#include <vector>

namespace AudioUtilities
{
    namespace Delay
    {

        /*
        A multitap, variable speed delay line inheriting from `BlendableCircleBuff` in
        "CircleBuffer.h".
        */
        class DelayBuffer : public Buffer::BlendableCircleBuffer<float>
        {
          public:

            DelayBuffer() : BlendableCircleBuffer() {}

            DelayBuffer(float delayMilliseconds, int sampleRate);

            // Write to the buffer then increment write position by
            // `writeSpeed`.
            virtual void write(float val) override;

            // Returns the sample at the current read index.
            // Increments the read index according to `readSpeed` after if
            // `autoIncrementReadex` is `true`.
            virtual float read();

            int getSampleRate() const;

            void setSampleRate(int rate);

            virtual float getDelayMilliseconds() const;

            virtual void setDelayMilliseconds(float ms);

            // Set the read speed.
            // If `tapNum` is -1, this speed will be applied to all taps.
            // Otherwise only the tap specified by `tapNum` will be set.
            virtual void setReadSpeed(float speed, int tapNum = -1);

            float getReadSpeed(int tapNum);

            // Returns a reference to the specified tap.
            // `0` is always the primary tap
            Tap& tap(int index);

            // Add a tap to the delay.
            // `delayRatio` is clamped between 0.0f and 1.0f.
            virtual void addTap(float delayRatio);

            // Remove the specfied tap.
            virtual void removeTap(int index);

            int getNumTaps();

            // If `tapNum` is -1, returns the gain for combined feedback.
            // Otherwise, returns the feedback gain for the given tap.
            float getFeedbackGain(int tapNum = -1);

            // If `tapNum` is -1, sets teh gain for combined feedback.
            // Otherwise, sets the feedback gain for the given tap.
            void setFeedbackGain(float val, int tapNum = -1);

            FeedbackType getFeedbackType(int tapNum);

            // If `tapNum` is -1, apply `type` to all taps.
            // Otherwise, just the specified `tapNum`.
            void setFeedbackType(FeedbackType type, int tapNum = -1);

            FeedbackSource getFeedbackSource();

            void setFeedbackSource(FeedbackSource source);

          protected:

            // Return `val` with feedback added to it.
            virtual float addFeedback(float val);

            // Returns the sum of each taps feedback element.
            virtual float readPerTapFeedback();

            // For the given tap, increment it's index if autoincrement is true.
            // Increment the static index whether autoincrement is true or false.
            virtual void incrementTap(Tap& tap);

            // Set the buffer size and configure taps.
            virtual void resize(int size) override;

            // Configure the given tap.
            virtual void configureTap(Tap& tap);

            // Configures all taps.
            virtual void configureTaps();

            std::vector<Tap> taps;
            int sampleRate = 44100;
            int delaySamples = 100;
            float delayMilliseconds = 1.0f;
            Feedback feedback;
        };
    } // namespace Delay
} // namespace AudioUtilities
