#pragma once

#include "CircleBuffer.h"
#include "Feedback.h"

namespace AudioUtilities
{
    namespace Delay
    {
        // A tap for reading from a delay line.
        class Tap
        {
          public:

            Tap() {}

            Tap(float ratio, bool isPrimary = false);

            int getDelaySamples() const;

            void setDelaySamples(int val);

            float getDelayRatio() const;

            // `val` is constrained b/t 0 and 1.0
            void setDelayRatio(float val);

            // Use this to ensure `index` and `staticIndex` both get their max set.
            void setMaxIndex(int val);

            // Use this to set both `index` and `staticIndex` to the given value.
            void setIndex(int val);

            // Increment `index` by `readSpeed` and increment `staticIndex` by 1.
            virtual void increment();

            bool isPrimary() const;

            const Buffer::BufferIndex& getStaticIndex();

            void incrementStaticIndex();

            Feedback feedback;
            Buffer::BufferIndex index;
            float gain = 1.0f;
            float readSpeed = 1.0f;

          private:

            // Not sure how to ensure these are synced w/o storing sample rate and max
            // delay time
            float delayRatio = 1.0f;
            int delaySamples = 1;
            bool primaryTap = false;
            // This one is used to keep a fixed readspeed of 1.
            Buffer::BufferIndex staticIndex;
        };
    } // namespace Delay
} // namespace AudioUtilities