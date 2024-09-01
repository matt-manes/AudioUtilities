#pragma once

#include "CircleBuff.h"
#include "SampleRate.h"
#include <vector>

namespace AudioUtilities
{
    namespace DelayLine
    {
        /*
        A variable speed delay line inheriting from `CircleBuff` in
        "CircleBuff.h".
        */
        class DelayLine : public CircleBuff::CircleBuff<float>
        {
          public:

            DelayLine() : CircleBuff() {}

            DelayLine(float delayMilliseconds, int sampleRate);

            // Set to `false` to handle updating the read index manually.
            bool autoIncrementReadex = true;

            // Returns the sample at the current read index.
            // Increments the read index after if `autoIncrementReadex` is
            // `true`.
            float read();

            int getSampleRate() const;

            void setSampleRate(int rate);

            float getDelayMilliseconds() const;

            void setDelayMilliseconds(float ms);

            // Returns a pointer to the read `Index` object.
            Index::Index *getReadex();

            // The amount the read `Index` is moved when `autoIncrementReadex`
            // is `true`.
            float getReadSpeed() const;

            // Set the amount the read `Index` is moved when
            // `autoIncrementReadex` is `true`.
            void setReadSpeed(float speed);

          protected:

            void resize(int size) override;

            // Increment `readex` according to `readspeed`.
            virtual void incrementRead();

            Index::Index readex;
            int writeSpeed = 1;
            float readSpeed = 1;
            int sampleRate = 1;
            int delaySamples = 1;
            float delayMilliseconds = 1.0f;
        };
    } // namespace DelayLine
} // namespace AudioUtilities
