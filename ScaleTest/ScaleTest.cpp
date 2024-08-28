#include "../AudioUtilities/Scale.h"
#include "CppUnitTest.h"

// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ScaleTest
{
    TEST_CLASS(ScaleTest)
    {
      public:

        TEST_METHOD(TestScale) 
        {
            AudioUtilities::Range::Range<float> oldRange(0.0f, 1.0f);
            AudioUtilities::Range::Range<float> newRange(100.0f, -100.0f);
            float input = 0.5f;
            Assert::AreEqual(0.0f, 
                            AudioUtilities::Scale::scale(input, oldRange, newRange),
                            0.001f);
            input = 10.0f;
            Assert::AreEqual(6.0f, 
                            AudioUtilities::Scale::scale(input, 0.0f, 100.0f, 5.0f, 15.0f), 
                            0.001f
            );
            Assert::AreEqual(14.0f, 
                            AudioUtilities::Scale::scale(input, 0.0f, 100.0f, 15.0f, 5.0f), 
                            0.001f
            );
        }

        TEST_METHOD(TestScaleClass)
        {
            AudioUtilities::Scale::Scale scale(
                AudioUtilities::Range::Range<float>(0.0f, 1.0f), 
                AudioUtilities::Range::Range<float>(100.0f, -100.0f)
            );
            Assert::AreEqual(0.0f, scale.fromAToB(0.5f), 0.001f);
            Assert::AreEqual(0.5f, scale.fromBToA(0.0f), 0.001f);
            
            // a should b 0->100
            scale.a.setStop(100.0f);
            // b should be 5->15
            scale.b.setStart(5.0f);
            scale.b.setStop(15.0f);
            // scale .1 * a.delta() onto b
            Assert::AreEqual(6.0f, scale.fromAToB(10.0f), 0.001f);
            
            // b should be 15->5
            scale.b.reverse();
            // Should be b.start - .1 * b.delta
            Assert::AreEqual(14.0f, scale.fromAToB(10.0f), 0.001f);
        }
    };
}
