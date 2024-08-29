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

            // Should be called every loop where one loop is equivalent to one
            // sample at the sample rate.
            void tick();

            // This will call `tick()` for you and return the new value.
            // Don't use this and `tick()` or your ramp will be twice the speed.
            float getNextValue();

            // Start the ramp.
            inline void start() { active = true; }

            // Stop the ramp, freezing the current value.
            inline void stop() { active = false; }

            // Reset the ramp. If called while the ramp is active, it will jump
            // back to the starting value and continue ramping.
            void reset();

            // Returns `true` if the current ramp value is at the stop value.
            inline bool isFinished() const { return finished; }

            // Returns whether the ramp is currently ramping. A ramp can be
            // inactive, but unfinished, i.e. paused.
            inline bool isActive() const { return active; }

            // Returns `true` if this ramp is a falling ramp, i.e. the stop
            // value is less than the start value.
            inline bool isReverse() const { return range.isNegative(); }

            // Returns the step size added every `tick()` to the ramp value when
            // the ramp is active.
            inline float getStepSize() const { return stepSize; }

            // Returns the current value of the ramp.
            // Any curve for this ramp is applied when this function is called.
            // For best performance, call this function once and store in a
            // local variable.
            inline float getCurrentVal() { return curve.apply(currentVal); }

            // The starting value of this ramp.
            inline float getStart() const { return range.getStart(); }

            // Set the start value of this ramp.
            void setStart(float value);

            // The stop value of this ramp.
            inline float getStop() const { return range.getStop(); }

            // Set the stop value of this ramp.
            void setStop(float value);

            inline float getCurve() { return curve.getCurveFactor(); }

            // Set the curve of the ramp. Values are constrained to the interval
            // 0.01<->0.99.
            inline void setCurve(float value) { curve.setCurveFactor(value); }

            // Returns this ramp's length in samples.
            inline int getLengthSamples() const { return lengthSamples; }

            // Set ramp length in samples.
            void setLengthSamples(int samples);

            // Set ramp length in milliseconds.
            inline void setLengthMilliseconds(float milliseconds)
            {
                setLengthSamples(
                    SampleRate::fromMilliseconds(milliseconds, sampleRate)
                );
            }

            void setLengthSteps(int numSteps);

            inline void setFreeRunning(bool value) { freeRunning = value; }

            inline void setBidirectional(bool value) { bidirectional = value; }

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
            bool freeRunning = false;
            bool bidirectional = false;

            inline void calculateStepSize()
            {
                stepSize = range.getStepSize(lengthSamples);
            }

            // Make sure `currentVal` doesn't accidentally exceed stop value
            inline void clampCurrentVal()
            {
                currentVal = Clamp::clamp(currentVal, range);
            }

            // This can be overridden to implement different ramp shapes.
            inline virtual void incrementCurrentVal()
            {
                currentVal += stepSize;
            }

            bool stopValueReached() const;
        };
    } // namespace Ramp
} // namespace AudioUtilities
