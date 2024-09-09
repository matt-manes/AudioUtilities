#include "Index.h"

AudioUtilities::Index::Index::Index()
{
    setBounds(0, 1);
}

AudioUtilities::Index::Index::Index(int maxIndex)
{
    setBounds(0, maxIndex);
}

AudioUtilities::Index::Index::Index(int minIndex, int maxIndex)
{
    setBounds(minIndex, maxIndex);
}

AudioUtilities::Index::Index::Index(Range::Range<int> bounds)
{
    setBounds(bounds);
}

int AudioUtilities::Index::Index::getPaddedMax()
{
    return paddedBounds.getStop();
}

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

bool AudioUtilities::Index::Index::isOutOfBounds()
{
    return !(paddedBounds.contains(full, Range::Inclusion::Start));
}

bool AudioUtilities::Index::Index::isInPaddedZone()
{
    return paddedZone.contains(full, Range::Inclusion::None);
}

void AudioUtilities::Index::Index::setMin(int val)
{
    setBounds(val, bounds.getStop());
};

void AudioUtilities::Index::Index::setMax(int val)
{
    setBounds(bounds.getStart(), val);
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

AudioUtilities::Range::Range<int> AudioUtilities::Index::Index::getBounds()
{
    return bounds;
}

void AudioUtilities::Index::Index::splitIndex()
{
    lower = (int)full;
    decimal = full - lower;
    upper = lower + 1;
    if (upper > bounds.getUpper())
    {
        upper = bounds.getLower();
    }
}

AudioUtilities::Range::Range<int> AudioUtilities::Index::Index::enforceBoundsConstraints(
    Range::Range<int> bounds
)
{
    if (bounds.getStart() < 0)
    {
        bounds.setStart(0);
    }
    if (bounds.getStop() < 0)
    {
        bounds.setStop(0);
    }
    if (bounds.isNegative())
    {
        bounds.reverse();
    }
    return bounds;
}

void AudioUtilities::Index::Index::setIndex(float val)
{
    full = val;
    wrap();
    splitIndex();
}

float AudioUtilities::Index::Index::getFull() const
{
    return full;
}

int AudioUtilities::Index::Index::getUpper() const
{
    return upper;
}

int AudioUtilities::Index::Index::getLower() const
{
    return lower;
}

float AudioUtilities::Index::Index::getDecimal() const
{
    return decimal;
}

int AudioUtilities::Index::Index::getMin() const
{
    return bounds.getStart();
}

int AudioUtilities::Index::Index::getMax() const
{
    return bounds.getStop();
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator=(float val)
{
    setIndex(val);
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator+(float val)
{
    setIndex(full + val);
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator-(float val)
{
    setIndex(full - val);
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator*(float val)
{
    setIndex(full * val);
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator/(float val)
{
    setIndex(full / val);
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator+=(float val)
{
    *this = *this + val;
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator-=(float val)
{
    *this = *this - val;
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator*=(float val)
{
    *this = *this * val;
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator/=(float val)
{
    *this = *this / val;
    return *this;
}

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator++()
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

AudioUtilities::Index::Index& AudioUtilities::Index::Index::operator--()
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
