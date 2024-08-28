#pragma once

namespace AudioUtilities
{
    namespace SampleRate
    {
        // Returns the corresponding number of samples for `seconds` given
        // `sampleRate`.
        inline int fromSeconds(float seconds, int sampleRate)
        {
            return (int)(seconds * sampleRate);
        }

        // Returns the corresponding number of samples for `milliseconds` given
        // `sampleRate`.
        inline int fromMilliseconds(float milliseconds, int sampleRate)
        {
            return (int)(fromSeconds(milliseconds, sampleRate) * 0.001f);
        }

        // Returns the corespoding number of seconds for `samples` given
        // `sampleRate`.
        inline float toSeconds(int samples, int sampleRate)
        {
            return (float)samples / (float)sampleRate;
        }

        // Returns the corespoding number of milliseconds for `samples` given
        // `sampleRate`.
        inline float toMilliseconds(int samples, int sampleRate)
        {
            return toSeconds(samples, sampleRate) * 1000.0f;
        }

        /*
        Convert between seconds/milliseconds and samples for a given sample
        rate.
        */
        class Converter
        {
          public:

            Converter(int sampleRate) : sampleRate(sampleRate) {}

            // Returns the corresponding number of samples for `seconds`.
            inline int fromSeconds(float seconds) const
            {
                return SampleRate::fromSeconds(seconds, sampleRate);
            }

            // Returns the corresponding number of samples for `milliseconds`.
            inline int fromMilliseconds(float milliseconds) const
            {
                return SampleRate::fromMilliseconds(milliseconds, sampleRate);
            }

            // Returns the corespoding number of seconds for `samples`.
            inline float toSeconds(int samples) const
            {
                return SampleRate::toSeconds(samples, sampleRate);
            }

            // Returns the corespoding number of milliseconds for `samples`.
            inline float toMilliseconds(int samples) const
            {
                return SampleRate::toMilliseconds(samples, sampleRate);
            }

            inline int getSampleRate() const { return sampleRate; }

            inline void setSampleRate(int sampleRate)
            {
                this->sampleRate = sampleRate;
            }

          private:

            int sampleRate;
        };
    } // namespace SampleRate
} // namespace AudioUtilities