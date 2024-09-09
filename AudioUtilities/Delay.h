#pragma once

#include "DelayBuffer.h"
#include "PingPongBuffer.h"
#include "Blend.h"
#include "Clamp.h"
#include <vector>

namespace AudioUtilities
{
    namespace Delay
    {
        enum BufferType
        {
            Circle,
            PingPong
        };

        // A multi-tap, variable speed delay block.
        class Delay
        {
          public:

            Delay() {}

            Delay(
                float delayMilliseconds, int sampleRate, BufferType bufferType = Circle
            );

            // Write to delay.
            // Handles adding feedback signal.
            virtual void write(float val);

            // Read all taps and store feedback.
            virtual float read();

            // Writes the sample to the delay line and returns the sample blended with
            // delay output.
            // `blend` is clamped to the range 0<->1 where 0 is full dry and 1 is full
            // wet.
            float process(float input, float blend);

            // Writes the sample to the delay line and returns the sample blended with
            // delay output using this instance's internal `blend` value.
            float process(float input);

            virtual float getBlend();

            // Values are clamped to the range 0<->1 where 0 is full dry and 1 is full
            // wet.
            virtual void setBlend(float val);

            int getSampleRate();

            void setSampleRate(int val);

            float getDelayMilliseconds();

            void setDelayMilliseconds(float val);

            // The underlying buffer type.
            BufferType getBufferType();

            DelayBuffer buffer;

          protected:

            virtual float __process(float input, float blend);

            float blend = 0.5f;
            BufferType bufferType = Circle;
            int sampleRate = 1;
            float delayMilliseconds = 1;
        };

        /*
        Container for handling multiple Delay blocks.

        Member functions will apply to all channels.

        Use public member vector `channels` to operate on specific channels.
        */
        struct MultiChannelDelay
        {

            MultiChannelDelay() {}

            MultiChannelDelay(
                int numChannels,
                float delayMilliseconds,
                int sampleRate,
                BufferType bufferType = Circle
            );

            MultiChannelDelay(std::vector<Delay>& channels);

            // Set sample rate for all channels.
            void setSampleRate(int rate);

            int getSampleRate();

            // Sets delay time for all channels.
            void setDelayMilliseconds(float ms);

            // Sets readspeed for all taps of all channels.
            void setReadSpeed(float speed);

            // Set the read speed on all channels for the given tap.
            // Be careful about indexing if this instance was created from a pre-created
            // vector of `Delay` blocks that don't all have the same number of taps.
            void setReadSpeed(float speed, int tapNum);

            // Add a tap to all channels.
            void addTap(float delayRatio);

            // Be careful about indexing if this instance was created from a pre-created
            // vector of `Delay` blocks that don't all have the same number of taps.
            void removeTap(int index);

            // Set the feedback gain for all taps for all channels
            void setFeedbackGain(float val);

            void setBlend(float val);

            // Set feedback type for all taps for all channels
            void setFeedbackType(FeedbackType feedbackType);

            std::vector<Delay> channels;

          private:

            int sampleRate = 1;
        };
    } // namespace Delay
} // namespace AudioUtilities