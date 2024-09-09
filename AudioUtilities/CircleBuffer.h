#pragma once

#include "Index.h"
#include "Blend.h"
#include <vector>

namespace AudioUtilities
{
    namespace Buffer
    {
        class BufferIndex : public Index::Index
        {
          public:

            using Index::Index;
            bool autoIncrement = true;
        };

        template <class T> class CircleBuffer
        {
          public:

            CircleBuffer() {};

            CircleBuffer(int size)
            {
                resize(size);
            }

            CircleBuffer(std::vector<T>& buffer)
            {
                data = buffer;
                // Call resize to set things dependent on the buffer size.
                resize(data.size());
            }

            // ========================== Write ========================== //

            // Write to the buffer then increment write position
            inline virtual void write(T val)
            {
                data[writedex.getLower()] = val;
                if (writedex.autoIncrement == true)
                {
                    incrementWritedex();
                }
            }

            // Write to the buffer at the given index, wrapping if necessary
            // Note: does not increment internal write pointer
            inline virtual void write(T val, int index)
            {
                data[index % data.size()] = val;
            }

            // Write to the buffer at the given `Index`
            // Note: does not increment internal write pointer
            inline virtual void write(T val, Index::Index index)
            {
                write(val, index.getLower());
            }

            // ========================== Read ========================== //

            // Reads from the buffer then, if `readex.autoIncrement == true`, increment
            // read position.
            // virtual T read();

            inline virtual T read(int index) const
            {
                return data[index % data.size()];
            }

            inline T operator[](int index) const
            {
                return read(index);
            }

            // ===========================================================  //

            // The size of this buffer
            inline int size()
            {
                return data.size();
            }

            // Resize the buffer and write indexer
            inline virtual void resize(int size)
            {
                data.resize(size);
                writedex.setMax(size - 1);
            }

            // Reset all indicies to default values
            inline virtual void flush()
            {
                data.assign(data.size(), T());
            }

            // Returns a pointer to the writing `Index` object
            inline const BufferIndex& getWritedex()
            {
                return writedex;
            }

            // Returns the index that will be written to on the next call to
            // `write(val)`
            inline int getWritePosition()
            {
                return writedex.getLower();
            }

            // Returns the underlying data vector
            inline const std::vector<T>& getData()
            {
                return data;
            }

            virtual inline void incrementWritedex()
            {
                ++writedex;
            }

            inline void resetWritedex()
            {
                writedex = 0;
            }

          protected:

            std::vector<T> data;

            BufferIndex writedex;
        };

        // ========================================================================================
        // ========================================================================================
        // ========================================================================================

        /*
        Circle buffer that supports reading in between indicies.
        Requires that `T` is castable to a float.
        */
        template <class T> class BlendableCircleBuffer : public CircleBuffer<T>
        {
          public:

            using CircleBuffer<T>::CircleBuffer;

            inline virtual float read(Index::Index index)
            {
                return Blend::blend(
                    this->data[index.getLower()],
                    this->data[index.getUpper()],
                    index.getDecimal()
                );
            }

            inline virtual float read(float index)
            {
                Index::Index readex(this->data.size() - 1);
                readex = index;
                return this->read(readex);
            }

            inline float operator[](Index::Index index)
            {
                return read(index);
            }

            inline float operator[](float index)
            {
                return read(index);
            }
        };
    } // namespace Buffer
} // namespace AudioUtilities