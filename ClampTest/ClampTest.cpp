#include "../AudioUtilities/Clamp.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClampTest 
{
TEST_CLASS(ClampTest)
{
  public :
    TEST_METHOD(TestClamp)
    {
        Assert::AreEqual(0.0f, AudioUtilities::Clamp::clamp(-1.0f, 0.0f, 1.0f), 0.001f);
        Assert::AreEqual(0.5f, AudioUtilities::Clamp::clamp(0.5f, 0.0f, 1.0f), 0.001f);
        Assert::AreEqual(1.0f, AudioUtilities::Clamp::clamp(1.5f, 0.0f, 1.0f), 0.001f);
    }

    TEST_METHOD(TestClampRange)
    {
        AudioUtilities::Range::Range<float> range(-1.0f, 1.0f);
        Assert::AreEqual(-1.0f, AudioUtilities::Clamp::clamp(-5.0f, range));
        Assert::AreEqual(0.0f, AudioUtilities::Clamp::clamp(0.0f, range));
        Assert::AreEqual(1.0f, AudioUtilities::Clamp::clamp(100.0f, range));
    }
};
}
