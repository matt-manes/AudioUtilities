#pragma once

#include "Taper.h"
#include "Range.h"
#include "Clamp.h"
#include "SampleRate.h"

namespace AudioUtilities
{
    namespace Ramp
    {
        /*
        Generate simple rising or falling ramps with optional exponential or
        log curvature. Be sure to either call this instance's `tick()` method
        or `getNextValue()` method in every loop that corresponds to the given
        sample rate.
        */
        class Ramp
        {
          public:

            Ramp();

            Ramp(
                float lengthMilliseconds,
                int sampleRate,
                float startVal = 0.0f,
                float stopVal = 1.0f,
                float curveFactor = 0.5f
            );

            Ramp(
                int lengthSamples,
                int sampleRate,
                float startVal = 0.0f,
                float stopVal = 1.0f,
                float curveFactor = 0.5f
            );

            // Whether this ramp automatically restarts after finishing.
            bool freeRunning = false;

            // Whether this ramp changes directions after each completion.
            bool bidirectional = false;

            // Should be called every loop where one loop is equivalent to one
            // sample at the sample rate.
            void tick();

            // This will call `tick()` for you and return the new value.
            // Don't use this and `tick()` or your ramp will be twice the speed.
            float getNext();

            // Start the ramp.
            void start();

            // Stop the ramp, freezing the current value.
            void stop();

            // Reset the ramp. If called while the ramp is active, it will jump
            // back to the starting value and continue ramping.
            void reset();

            // Returns `true` if the current ramp value is at the stop value.
            bool isFinished() const;

            // Returns whether the ramp is currently ramping. A ramp can be
            // inactive, but unfinished, i.e. paused.
            bool isActive() const;

            // Returns `true` if this ramp is a falling ramp, i.e. the stop
            // value is less than the start value.
            bool isReverse() const;

            // Returns the step size added every `tick()` to the ramp value when
            // the ramp is active.
            float getStepSize() const;

            // Returns the current value of the ramp.
            // Any curve for this ramp is applied when this function is called.
            // For best performance, call this function once and store in a
            // local variable.
            float read();

            // The starting value of this ramp.
            float getStart() const;

            // Set the start value of this ramp.
            void setStart(float val);

            // The stop value of this ramp.
            float getStop() const;

            // Set the stop value of this ramp.
            void setStop(float val);

            float getCurve();

            // Set the curve of the ramp. Values are constrained to the interval
            // 0.01<->0.99.
            void setCurve(float val);

            // Returns this ramp's length in samples.
            int getLengthSamples() const;

            // Set ramp length in samples.
            void setLengthSamples(int samples);

            // Set ramp length in milliseconds.
            void setLengthMilliseconds(float milliseconds);

            void setLengthSteps(int numSteps);

            // Reverse this ramp's direction.
            void reverse();

          protected:

            int sampleRate, lengthSamples;
            bool active = false;
            bool finished = false;
            // The endpoints of this ramp.
            Range::Range<float> range = Range::Range<float>(0.0f, 1.0f);
            float currentVal = 0.0f;
            float stepSize;
            Taper::Taper curve;

            void calculateStepSize();

            // Make sure `currentVal` doesn't accidentally exceed stop value.
            void clampCurrentVal();

            // This can be overridden to implement different ramp shapes.
            virtual void incrementCurrentVal();

            bool stopValueReached() const;
        };
    } // namespace Ramp
} // namespace AudioUtilities
