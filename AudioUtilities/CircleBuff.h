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

            // Write to the buffer then increment write position
            virtual void write(T val);

            // Write to the buffer at the given index, wrapping if necessary
            // Note: does not increment internal write pointer
            virtual void write(T val, int index);

            // Write to the buffer at the given `Index`
            // Note: does not increment internal write pointer
            virtual void write(T val, Index::Index index);

            // ========================== Read ========================== //

            T read(int index) const;

            // Will only work with types that define `+`, `*`, and `-` operators
            // and can be converted to a float.
            // Interpolates between two nearest values if `index` has a decimal
            // component
            float read(Index::Index index) const;

            // Will only work with types that define `+`, `*`, and `-` operators
            // and can be converted to a float.
            // Interpolates between two nearest values if `index` has a decimal
            // component
            float read(float index) const;

            T operator[](int index) const;

            // Will only work with types that define `+`, `*`, and `-` operators
            // and can be converted to a float.
            // Interpolates between two nearest values if `index` has a decimal
            // component
            float operator[](Index::Index index) const;

            // Will only work with types that define `+`, `*`, and `-` operators
            // and can be converted to a float.
            // Interpolates between two nearest values if `index` has a decimal
            // component
            float operator[](float index) const;

            // ===========================================================  //

            // The size of this buffer
            int size();

            // Resize the buffer and write indexer
            virtual void resize(int size);

            // Reset all indicies to default values
            void flush();

            // Returns a pointer to the writing `Index` object
            Index::Index *getWritedex();

            // Returns the index that will be written to on the next call to
            // `write(val)`
            int getWritePosition();

            // Returns the underlying data vector
            std::vector<T> *getData();

          protected:

            std::vector<T> data;

            Index::Index writedex;
        };

        template <class T> inline void CircleBuff<T>::write(T val)
        {
            data[writedex++.getLower()] = val;
        }

        template <class T> inline void CircleBuff<T>::write(T val, int index)
        {
            data[index % data.size()] = val;
        }

        template <class T>
        inline void CircleBuff<T>::write(T val, Index::Index index)
        {
            index.setBounds(0, data.size() - 1);
            write(val, index.getLower());
        }

        template <class T> inline T CircleBuff<T>::read(int index) const
        {
            return data[index % data.size()];
        }

        template <class T>
        inline float CircleBuff<T>::read(Index::Index index) const
        {
            index.setBounds(0, data.size() - 1);
            return Blend::blend(
                data[index.getLower()],
                data[index.getUpper()],
                index.getDecimal()
            );
        }

        template <class T> inline float CircleBuff<T>::read(float index) const
        {
            Index::Index readex(data.size() - 1);
            readex = index;
            return read(readex);
        }

        template <class T> inline T CircleBuff<T>::operator[](int index) const
        {
            return read(index);
        }

        template <class T>
        inline float CircleBuff<T>::operator[](Index::Index index) const
        {
            return read(index);
        }

        template <class T>
        inline float CircleBuff<T>::operator[](float index) const
        {
            return read(index);
        }

        template <class T> inline int CircleBuff<T>::size()
        {
            return data.size();
        }

        template <class T> inline void CircleBuff<T>::resize(int size)
        {
            data.resize(size);
            writedex.setMax(size - 1);
        }

        template <class T> inline void CircleBuff<T>::flush()
        {
            data.assign(data.size(), T());
        }

        template <class T> inline Index::Index *CircleBuff<T>::getWritedex()
        {
            return &writedex;
        }

        template <class T> inline int CircleBuff<T>::getWritePosition()
        {
            return writedex.getLower();
        }

        template <class T> inline std::vector<T> *CircleBuff<T>::getData()
        {
            return &data;
        }
    } // namespace CircleBuff
} // namespace AudioUtilities