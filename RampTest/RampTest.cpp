#include "../AudioUtilities/Ramp.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RampTest 
{
TEST_CLASS(RampTest)
{
  public:

    TEST_METHOD(TestConstruction)
    {
        AudioUtilities::Ramp::Ramp ramp = AudioUtilities::Ramp::Ramp(500.0f, 1000, 0.0f, 1.0f);
        Assert::AreEqual(0.0f, ramp.read(), 0.00001f);
        Assert::IsFalse(ramp.isActive());
        Assert::AreEqual(1.0f/500.0f, ramp.getStepSize(), 0.00001f);
        Assert::AreEqual(500, ramp.getLengthSamples());
    }

    // All ramp tests should have a ramp lenght of 500 samples.
    // Starting the ramp at `100` should mean `350` is the mid point of the ramp.
    TEST_METHOD(TestRamp)
    {
        AudioUtilities::Ramp::Ramp ramp = AudioUtilities::Ramp::Ramp(500.0f, 1000, 0.0f, 1.0f);
        for (int i = 0; i < 1000; i++)
        {
			if (i < 100)
            {
                Assert::IsFalse(ramp.isActive());
                Assert::AreEqual(ramp.getStart(), ramp.read());
            }
            if (i == 100) { ramp.start();}
            if (i == 350) { Assert::AreEqual(0.5f, ramp.read(), 0.00001f); }
            if (i > 600) 
            {
                Assert::AreEqual(ramp.getStop(), ramp.read(), 0.00001f);
                Assert::IsFalse(ramp.isActive());
            }
            ramp.tick();
		}
    }

    // All ramp tests should have a ramp lenght of 500 samples.
    // Starting the ramp at `100` should mean `350` is the mid point of the ramp.
    TEST_METHOD(TestRampGetNext)
    {
        AudioUtilities::Ramp::Ramp ramp = 
            AudioUtilities::Ramp::Ramp(500.0f, 1000, 0.0f, 1.0f);
        float currentValue;
        for (int i = 0; i < 1000; i++)
        {
            currentValue = ramp.getNext();
			if (i < 100)
            {
                Assert::IsFalse(ramp.isActive());
                Assert::AreEqual(ramp.getStart(), currentValue);
            }
            if (i == 100) { ramp.start();}
            if (i == 350) { Assert::AreEqual(0.5f, currentValue, 0.00001f); }
            if (i > 600) 
            {
                Assert::AreEqual(ramp.getStop(), currentValue, 0.00001f);
                Assert::IsFalse(ramp.isActive());
            }
		}
    }

    TEST_METHOD(TestReverseRamp)
    {
        AudioUtilities::Ramp::Ramp ramp = 
            AudioUtilities::Ramp::Ramp(500.0f, 1000, 1.0f, 0.0f);
        Assert::IsTrue(ramp.getStepSize() < 0);
        for (int i = 0; i < 1000; i++)
        {
			if (i < 100)
            {
                Assert::IsFalse(ramp.isActive());
                Assert::AreEqual(ramp.getStart(), ramp.read());
            }
            if (i == 100) { ramp.start();}
            if (i == 350) { Assert::AreEqual(0.5f, ramp.read(), 0.00001f); }
            if (i > 600) 
            {
                Assert::AreEqual(ramp.getStop(), ramp.read(), 0.00001f);
                Assert::IsFalse(ramp.isActive());
            }
            ramp.tick();
		}
    }

    TEST_METHOD(TestExpRamp)
    {
        AudioUtilities::Ramp::Ramp ramp = 
            AudioUtilities::Ramp::Ramp(500.0f, 1000, 0.0f, 1.0f, 0.1f);
        for (int i = 0; i < 1000; i++)
        {
			if (i < 100)
            {
                Assert::IsFalse(ramp.isActive());
                Assert::AreEqual(ramp.getStart(), ramp.read());
            }
            if (i == 100) 
            { 
                ramp.start();
            }
            if (i == 350) { Assert::AreEqual(0.1f, ramp.read(), 0.00001f); }
            if (i > 600) 
            {
                Assert::AreEqual(ramp.getStop(), ramp.read(), 0.00001f);
                Assert::IsFalse(ramp.isActive());
            }
            ramp.tick();
		}
    }

    TEST_METHOD(TestResetRamp)
    {
        AudioUtilities::Ramp::Ramp ramp = 
            AudioUtilities::Ramp::Ramp(500.0f, 1000, 0.0f, 1.0f);
        for (int i = 0; i < 1000; i++)
        {
			if (i < 100)
            {
                Assert::IsFalse(ramp.isActive());
                Assert::AreEqual(ramp.getStart(), ramp.read());
            }
            if (i == 100) { ramp.start(); }
            if (i == 350) { Assert::AreEqual(0.5f, ramp.read(), 0.00001f); }
            if (i == 400) {ramp.reset();}
            if (i == 650) { Assert::AreEqual(0.5f, ramp.read(), 0.00001f); }
            if (i > 900)
            {
                Assert::AreEqual(ramp.getStop(), ramp.read(), 0.00001f);
                Assert::IsFalse(ramp.isActive());
            }
            ramp.tick();
		}
    }
};
}
