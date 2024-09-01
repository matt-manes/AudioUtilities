#pragma once

#include "Ramp.h"
#include "SampleRate.h"

namespace AudioUtilities
{
    namespace Fade
    {
        // Enums representing the direction of the fade.
        enum Direction
        {
            In,
            Out
        };

        /*
        Apply an in or out fade to a signal.
        Be sure to call this instance's `tick()` method in every loop that
        corresponds to the given sample rate. See "Ramp.h" for more complete
        documentation.
        */
        class Fade : public Ramp::Ramp
        {
          public:

            Fade(
                float lengthMilliseconds,
                int sampleRate,
                Direction direction = Direction::In,
                float curveFactor = 0.5f
            );

            Fade(
                int lengthSamples,
                int sampleRate,
                Direction direction = Direction::In,
                float curveFactor = 0.5f
            );

            // Apply fade gain to sample.
            float apply(float val);

            // Will either be `Direction::In` or `Direction::Out`.
            Direction getDirection() const;

            // Set whether this is a fade in or a fade out.
            void setDirection(Direction direction);

          private:

            Direction direction;

            // use direction enum instead
            using Ramp::isReverse;

            // Fade start and stop should always be 0 and 1
            using Ramp::setStart;
            using Ramp::setStop;
        };
    } // namespace Fade
} // namespace AudioUtilities
