#include "Index.h"

void AudioUtilities::Index::Index::wrap()
{
    if (isOutOfBounds())
    {
        while (full < bounds.getLower())
        {
            full = bounds.getUpper() - (bounds.getLower() - full);
        }
        int whole = int(full);
        float decimal = std::abs(full - whole);
        int wrapped = ((whole - bounds.getLower()) % paddedBounds.getAbsDelta())
                      + bounds.getLower();
        full = (float)wrapped + decimal;
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
    this->bounds = enforceBoundsConstraints(bounds);
    int paddedMax = this->bounds.getStop() + 1;
    paddedBounds = Range::Range<int>(this->bounds.getStart(), paddedMax);
    paddedZone = Range::Range<int>(this->bounds.getStop(), paddedMax);
    wrap();
    splitIndex();
}

void AudioUtilities::Index::Index::splitIndex()
{
    lower = (int)full;
    decimal = full - lower;
    upper = lower + 1;
    if (upper > bounds.getUpper()) { upper = bounds.getLower(); }
}

AudioUtilities::Range::Range<int> AudioUtilities::Index::Index::
    enforceBoundsConstraints(Range::Range<int> bounds)
{
    if (bounds.getStart() < 0) { bounds.setStart(0); }
    if (bounds.getStop() < 0) { bounds.setStop(0); }
    if (bounds.isNegative()) { bounds.reverse(); }
    return bounds;
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
