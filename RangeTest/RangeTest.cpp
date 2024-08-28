#include "../AudioUtilities/Range.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RangeTest
{
    TEST_CLASS(RangeTest) 
    {
      public:

        TEST_METHOD(TestRange) 
        {
            AudioUtilities::Range::Range<float> range1(0.0f, 100.0f);
            Assert::AreEqual(100.0f, range1.getDelta(), 0.001f);
            range1.setStop(50.0f);
            Assert::AreEqual(50.0f, range1.getDelta(), 0.00001f);
        }

        TEST_METHOD(TestEquality)
        {
            AudioUtilities::Range::Range<float> range1(0.0f, 100.0f);
            AudioUtilities::Range::Range<float> range2(range1.getStart(), 
                                                range1.getStop());
            Assert::IsTrue(range1 == range2);
        }

        TEST_METHOD(TestReverse)
        {
            AudioUtilities::Range::Range<float> range1(0.0f, 100.0f);
            auto range2 = range1.getReversed();
            Assert::IsFalse(range1 == range2);
            Assert::IsTrue(range2.isNegative());
            Assert::IsFalse(range1.isNegative());
            Assert::AreEqual(0.0f, 
                            range1.getDelta() + range2.getDelta(), 
                            0.00001f);
            range1.reverse();
            Assert::IsTrue(range1 == range2);
        }

        TEST_METHOD(TestContains)
        {
            AudioUtilities::Range::Range<float> range(0.0f, 100.0f);
            Assert::IsTrue(range.contains(10.0f));
            Assert::IsFalse(range.contains(1000.0f));
            Assert::IsTrue(range.contains(0.0f));
            Assert::IsFalse(range.contains(0.0f, AudioUtilities::Range::Inclusion::None));
            Assert::IsTrue(range.contains(0.0f, AudioUtilities::Range::Inclusion::Start));
            Assert::IsFalse(range.contains(100.0f, AudioUtilities::Range::Inclusion::Start));
            Assert::IsTrue(range.contains(100.0f, AudioUtilities::Range::Inclusion::Upper));
            Assert::IsFalse(range.contains(0.0f, AudioUtilities::Range::Inclusion::Upper));

            range.reverse();
            Assert::IsTrue(range.contains(10.0f));
            Assert::IsFalse(range.contains(1000.0f));
            Assert::IsTrue(range.contains(0.0f));
            Assert::IsFalse(range.contains(0.0f, AudioUtilities::Range::Inclusion::None));
            Assert::IsTrue(range.contains(0.0f, AudioUtilities::Range::Inclusion::Stop));
            Assert::IsFalse(range.contains(100.0f, AudioUtilities::Range::Inclusion::Stop));
            Assert::IsTrue(range.contains(100.0f, AudioUtilities::Range::Inclusion::Upper));
            Assert::IsFalse(range.contains(0.0f, AudioUtilities::Range::Inclusion::Upper));
        }

        TEST_METHOD(TestStepSizes)
        {
            AudioUtilities::Range::Range<float> range(0.0f, 100.0f);
            Assert::AreEqual(10.0f, range.getStepSize(10), 0.00001f);
            Assert::AreEqual(10, range.getNumSteps(10.0f));
            range.setStop(101.0f);
            Assert::AreEqual(11, range.getNumSteps(10.0f));
            range.setBounds(0.0f, -100.0f);
            Assert::AreEqual(-10.0f, range.getStepSize(10), 0.00001f);
            Assert::AreEqual(10, range.getNumSteps(10.0f));
        }
    };
}
