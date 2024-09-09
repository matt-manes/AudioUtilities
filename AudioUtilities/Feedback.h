#pragma once

namespace AudioUtilities
{
    namespace Delay
    {
        // TODO: convert feedback options to a bit mask or something
        enum FeedbackType
        {
            Normal,
            Static
        };

        // The difference is in the gain.
        enum FeedbackSource
        {
            Combined,
            PerTap
        };

        class FeedbackSample
        {
          public:

            // Store a new feedback sample
            void write(float val);

            // Return the feedback sample multiplied by `gain`.
            float read();

            float gain = 0.0f;

          private:

            float sample = 0.0f;
        };

        class Feedback : public FeedbackSample
        {
          public:

            FeedbackSource source {Combined};
            FeedbackType type {Normal};
        };
    } // namespace Delay
} // namespace AudioUtilities