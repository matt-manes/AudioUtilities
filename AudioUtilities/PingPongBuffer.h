#pragma once

#include "DelayBuffer.h"
#include <vector>

namespace AudioUtilities
{
    namespace Delay
    {
        class PingPongDelayBuffer : public DelayBuffer
        {
            // Not sure taps will work how I expect when not using a single circular
            // buffer

          public:

            using DelayBuffer::DelayBuffer;

            virtual void write(float val) override;

            virtual float read() override;

            virtual float read(Index::Index index) override;

            virtual void setDelayMilliseconds(float ms) override;

            virtual void flush() override;

          protected:

            virtual void configureTap(Tap& tap) override;

            virtual void resize(int size) override;

            std::vector<float>& writeData = data;
            std::vector<float> readData;
            bool shouldSwap = false;
        };
    } // namespace Delay
} // namespace AudioUtilities