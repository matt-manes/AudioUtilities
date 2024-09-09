#include "Range.h"

template <class T> AudioUtilities::Range::Range<T>::Range()
{
    setBounds((T)0, (T)1);
}

template <class T> AudioUtilities::Range::Range<T>::Range(T start, T stop)
{
    setBounds(start, stop);
}

template <class T>
bool AudioUtilities::Range::Range<T>::operator==(const Range& other) const
{
    return (start == other.start) && (stop == other.stop);
}

template <class T> void AudioUtilities::Range::Range<T>::setBounds(T start, T stop)
{
    this->start = start;
    this->stop = stop;
    parseLowerUpper();
    calcDelta();
}

template <class T> void AudioUtilities::Range::Range<T>::setStart(T val)
{
    start = val;
    parseLowerUpper();
    calcDelta();
}

template <class T> void AudioUtilities::Range::Range<T>::setStop(T val)
{
    stop = val;
    parseLowerUpper();
    calcDelta();
}

template <class T> T AudioUtilities::Range::Range<T>::getStart() const
{
    return start;
}

template <class T> T AudioUtilities::Range::Range<T>::getStop() const
{
    return stop;
}

template <class T> T AudioUtilities::Range::Range<T>::getLower() const
{
    return std::fmin(start, stop);
}

template <class T> T AudioUtilities::Range::Range<T>::getUpper() const
{
    return std::fmax(start, stop);
}

template <class T> T AudioUtilities::Range::Range<T>::getDelta() const
{
    return delta;
}

template <class T> T AudioUtilities::Range::Range<T>::getAbsDelta() const
{
    return std::abs(delta);
}

template <class T> void AudioUtilities::Range::Range<T>::reverse()
{
    float tmp = start;
    start = stop;
    stop = tmp;
    parseLowerUpper();
    calcDelta();
}

template <class T>
AudioUtilities::Range::Range<T> AudioUtilities::Range::Range<T>::getReversed() const
{
    return Range(stop, start);
}

template <class T> bool AudioUtilities::Range::Range<T>::isNegative() const
{
    return delta < 0.0f;
}

template <class T> float AudioUtilities::Range::Range<T>::getStepSize(int numSteps)
{
    return delta / numSteps;
}

template <class T> int AudioUtilities::Range::Range<T>::getNumSteps(float stepSize)
{
    return std::abs((int)std::ceil(delta / stepSize));
}

template <class T>
bool AudioUtilities::Range::Range<T>::contains(float val, Inclusion boundsInclusion)
{
    switch (boundsInclusion)
    {
        case Both: return inclusion(val);
        case None: return noInclusion(val);
        case Lower: return lowerInclusion(val);
        case Upper: return upperInclusion(val);
        case Start:
        {
            if (isNegative())
            {
                return upperInclusion(val);
            }
            return lowerInclusion(val);
        }
        case Stop:
        {
            if (isNegative())
            {
                return lowerInclusion(val);
            }
            return upperInclusion(val);
        }
    }
}

template <class T> void AudioUtilities::Range::Range<T>::calcDelta()
{
    delta = stop - start;
}

template <class T> void AudioUtilities::Range::Range<T>::parseLowerUpper()
{
    if (start < stop)
    {
        lower = start;
        upper = stop;
    }
    else
    {
        lower = stop;
        upper = start;
    }
}

template <class T> bool AudioUtilities::Range::Range<T>::inclusion(float val)
{
    return (lower <= val) && (val <= upper);
}

template <class T> bool AudioUtilities::Range::Range<T>::lowerInclusion(float val)
{
    return (lower <= val) && (val < upper);
}

template <class T> bool AudioUtilities::Range::Range<T>::upperInclusion(float val)
{
    return (lower < val) && (val <= upper);
}

template <class T> bool AudioUtilities::Range::Range<T>::noInclusion(float val)
{
    return (lower < val) && (val < upper);
}

template AudioUtilities::Range::Range<float>;
template AudioUtilities::Range::Range<int>;