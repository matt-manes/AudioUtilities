#pragma once

#include "CircleBuff.h"
#include "SampleRate.h"
#include "Blend.h"
#include "Clamp.h"
#include <vector>

namespace AudioUtilities
{
    namespace DelayLine
    {
        class Tap
        {
          public:

            Tap() {}

            float getReadSpeed() const;

            void setReadSpeed(float val);

            float getGain() const;

            void setGain(float val);

            int getDelaySamples() const;

            void setDelaySamples(int samples);

            float getDelayRatio() const;

            // `val` is constrained b/t 0 and 1.0
            void setDelayRatio(float val);

            void increment();

            bool isPrimary() const;

            void setPrimary(bool primary);

            Index::Index getStaticIndex();

            Index::Index index;

          private:

            float gain = 1.0f;
            float readSpeed = 1.0f;
            // Not sure how to ensure these are synced w/o storing sample rate
            // and max delay time
            float delayRatio = 1.0f;
            int delaySamples = 1;
            bool primaryTap = false;
            // This index only gets incremented by one.
            Index::Index staticIndex;
        };

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
            bool autoIncrement = true;

            // Write to the buffer then increment write position by
            // `writeSpeed`.
            virtual void write(float val) override;

            // Returns the sample at the current read index.
            // Increments the read index according to `readSpeed` after if
            // `autoIncrementReadex` is `true`.
            virtual float read();

            int getSampleRate() const;

            void setSampleRate(int rate);

            float getDelayMilliseconds() const;

            virtual void setDelayMilliseconds(float ms);

            // Set the read speed for all taps.
            void setReadSpeed(float speed);

            // Set the read speed for a specific tap.
            void setReadSpeed(float speed, int tapNum);

            // The amount the write `Index` is moved when calling
            // `write(sample)`.
            float getWriteSpeed() const;

            // Set the amount the write `Index` is moved wehn calling
            // `write(sample)`.
            void setWriteSpeed(float speed);

            // Returns a reference to the specified tap.
            // `0` is always the primary tap
            Tap &tap(int index);

            // Add a tap to the delay.
            // `delayRatio` is clamped between 0.0f and 1.0f.
            void addTap(float delayRatio);

            // Remove the specfied tap.
            void removeTap(int index);

            int getNumTaps();

          protected:

            // Set the buffer size and configure taps.
            void resize(int size) override;

            // Configures the given tap
            void configureTap(int tapNum);

            // Configures all taps
            void configureTaps();

            std::vector<Tap> taps;
            int writeSpeed = 1;
            int sampleRate = 1;
            int delaySamples = 1;
            float delayMilliseconds = 1.0f;
        };
    } // namespace DelayLine
} // namespace AudioUtilities
