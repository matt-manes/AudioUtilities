#pragma once

#include "CircleBuff.h"
#include "SampleRate.h"
#include <vector>

namespace AudioUtilities
{
    namespace DelayLine
    {
        class DelayLine : public CircleBuff::CircleBuff<float>
        {
          public:

            DelayLine() : CircleBuff() {}

            DelayLine(float delayMilliseconds, int sampleRate);

            // Set to `false` to handle updating the read index manually
            bool autoIncrementReadex = true;

            float read();

            int getSampleRate() const { return sampleRate; }

            void setSampleRate(int rate);

            float getDelayMilliseconds() const { return delayMilliseconds; }

            void setDelayMilliseconds(float ms);

            Index::Index *getReadex() { return &readex; }

            float getReadSpeed() const { return readSpeed; }

            void setReadSpeed(float speed) { readSpeed = speed; }

          protected:

            void resize(int size) override;

            virtual void incrementRead() { readex += readSpeed; }

            Index::Index readex;
            int writeSpeed = 1;
            float readSpeed = 1;
            int sampleRate = 1;
            int delaySamples = 1;
            float delayMilliseconds = 1.0f;
        };
    } // namespace DelayLine
} // namespace AudioUtilities
