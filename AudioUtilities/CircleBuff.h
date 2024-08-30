#pragma once

#include "Index.h"
#include "Blend.h"
#include <vector>

namespace AudioUtilities
{
    namespace CircleBuff
    {
        template <class T> class CircleBuff
        {
          public:

            CircleBuff() {};

            CircleBuff(int size) { resize(size); }

            // Write to the buffer then increment write position
            virtual void write(T val) { data[writedex++.getLower()] = val; }

            // Write to the buffer at the given index, wrapping if necessary
            // Note: does not increment internal write pointer
            virtual void write(T val, int index)
            {
                data[index % data.size()] = val;
            }

            // Write to the buffer at the given `Index`
            // Note: does not increment internal write pointer
            virtual void write(T val, Index::Index index)
            {
                index.setBounds(0, data.size());
                write(val, index.getLower());
            }

            // Read from the buffer at the specified index
            T read(int index) { return data[index]; }

            T operator[](int index) const { return data[index % data.size()]; }

            // Will only work with types that define `+`, `*`, and `-` operators
            float operator[](Index::Index index) const
            {
                index.setBounds(0, data.size());
                return Blend::blend(
                    data[index.getLower()],
                    data[index.getUpper()],
                    index.getDecimal()
                );
            }

            // Will only work with types that define `+`, `*`, and `-` operators
            float operator[](float index) const
            {
                Index::Index readex(data.size());
                readex = index;
                return operator[](readex);
            }

            int size() { return data.size(); }

            // Resize the buffer and write indexer
            virtual void resize(int size)
            {
                data.resize(size);
                writedex.setMax(size - 1);
            }

            void flush() { data.assign(data.size(), T()); }

            Index::Index *getWritedex() { return &writedex; }

            int getWritePosition() { return writedex.getLower(); }

          private:

            std::vector<T> data;

            Index::Index writedex;
        };
    } // namespace CircleBuff
} // namespace AudioUtilities