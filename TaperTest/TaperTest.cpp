#include "../AudioUtilities/Taper.h"
#include "CppUnitTest.h"

// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaperTest 
{
TEST_CLASS(TaperTest)
{
    public :

        TEST_METHOD(ApplyTest)
        {
            AudioUtilities::Taper::Taper taper = AudioUtilities::Taper::Taper(0.1f, 0.0f, 1.0f);
            Assert::AreEqual(0.1f, taper.apply(0.5f), 0.001f);
            taper.setCurveFactor(0.9f);
            Assert::AreEqual(0.9f, taper.apply(0.5f), 0.001f);
        }

        TEST_METHOD(ConstructFromTypeTest)
        {
            AudioUtilities::Taper::Taper taper = AudioUtilities::Taper::Taper(AudioUtilities::Taper::Type::Exp);
            Assert::AreEqual(0.1f, taper.apply(0.5f), 0.001f);
            taper = AudioUtilities::Taper::Taper(AudioUtilities::Taper::Type::Log);
            Assert::AreEqual(0.9f, taper.apply(0.5f), 0.001f);
        }

        TEST_METHOD(ScalingTest)
        {
            AudioUtilities::Taper::Taper taper(0.1f, AudioUtilities::Range::Range<float>(100.0f, 200.0f));
            Assert::AreEqual(110.0f, taper.apply(150.0f), 0.001f);
            taper.setInputRange(AudioUtilities::Range::Range<float>(200.0f, 100.0f));
            Assert::AreEqual(190.0f, taper.apply(150.0f), 0.001f);
        }

};
}
