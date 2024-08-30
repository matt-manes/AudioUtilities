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

            // ========================== Write ========================== //
            //
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
                index.setBounds(0, data.size() - 1);
                write(val, index.getLower());
            }

            // ========================== Read ========================== //

            // Read from the buffer at the specified index
            T read(int index) { return data[index % data.size()]; }

            T operator[](int index) const { return data[index % data.size()]; }

            // Will only work with types that define `+`, `*`, and `-` operators
            // and can be converted to a float.
            // Interpolates between two nearest values if `index` has a decimal
            // component
            float operator[](Index::Index index) const
            {
                index.setBounds(0, data.size() - 1);
                return Blend::blend(
                    data[index.getLower()],
                    data[index.getUpper()],
                    index.getDecimal()
                );
            }

            // Will only work with types that define `+`, `*`, and `-` operators
            // and can be converted to a float.
            // Interpolates between two nearest values if `index` has a decimal
            // component
            float operator[](float index) const
            {
                Index::Index readex(data.size() - 1);
                readex = index;
                return operator[](readex);
            }

            // ===========================================================  //

            // The size of this buffer
            int size() { return data.size(); }

            // Resize the buffer and write indexer
            virtual void resize(int size)
            {
                data.resize(size);
                writedex.setMax(size - 1);
            }

            // Reset all indicies to default values
            void flush() { data.assign(data.size(), T()); }

            // Returns a pointer to the writing `Index` object
            Index::Index *getWritedex() { return &writedex; }

            // Returns the index that will be written to on the next call to
            // `write(val)`
            int getWritePosition() { return writedex.getLower(); }

            // Returns the underlying data vector
            inline std::vector<T> *getData() { return &data; }

          protected:

            std::vector<T> data;

            Index::Index writedex;
        };
    } // namespace CircleBuff
} // namespace AudioUtilities