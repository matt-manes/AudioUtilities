#include "Index.h"

void AudioUtilities::Index::Index::wrap()
{
    if (isOutOfBounds())
    {
        int whole = (int)full;
        float partial = full - whole;
        int wrapped = (whole % (getPaddedMax() - getMin())) + getMin();
        full = (float)wrapped + partial;
    }
}

void AudioUtilities::Index::Index::setMin(int value)
{
    setBounds(value, bounds.getStop());
};

void AudioUtilities::Index::Index::setMax(int value)
{
    setBounds(bounds.getStart(), value);
};

void AudioUtilities::Index::Index::setBounds(int min, int max)
{
    setBounds(Range::Range<int>(min, max));
}

void AudioUtilities::Index::Index::setBounds(Range::Range<int> bounds)
{
    this->bounds = bounds;
    int paddedMax = bounds.getStop() + 1;
    paddedBounds = Range::Range<int>(this->bounds.getStart(), paddedMax);
    paddedZone = Range::Range<int>(this->bounds.getStop(), paddedMax);
    wrap();
    splitIndex();
}

void AudioUtilities::Index::Index::splitIndex()
{
    lower = (int)full;
    decimal = full - lower;
    if (isInPaddedZone()) { upper = bounds.getStart(); }
    else { upper = lower + 1; }
}

void AudioUtilities::Index::Index::setIndex(float value)
{
    full = value;
    wrap();
    splitIndex();
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator=(
    float value
)
{
    setIndex(value);
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator+(
    float value
)
{
    setIndex(full + value);
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator-(
    float value
)
{
    setIndex(full - value);
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator*(
    float value
)
{
    setIndex(full * value);
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator/(
    float value
)
{
    setIndex(full / value);
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator+=(
    float value
)
{
    *this = *this + value;
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator-=(
    float value
)
{
    *this = *this - value;
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator*=(
    float value
)
{
    *this = *this * value;
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator/=(
    float value
)
{
    *this = *this / value;
    return *this;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator++()
{
    *this = *this + 1;
    return *this;
}

AudioUtilities::Index::Index AudioUtilities::Index::Index::operator++(int)
{
    Index tmp = *this;
    ++*this;
    return tmp;
}

AudioUtilities::Index::Index &AudioUtilities::Index::Index::operator--()
{
    *this = *this - 1;
    return *this;
}

AudioUtilities::Index::Index AudioUtilities::Index::Index::operator--(int)
{
    Index tmp = *this;
    --*this;
    return tmp;
}
