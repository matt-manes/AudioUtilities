#include "../AudioUtilities/Blend.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlendTest {
TEST_CLASS(BlendTest)
{
    public :

        TEST_METHOD(TestBlend){
            float val1 = -1.0f;
            float val2 = 1.0f;
            Assert::AreEqual(-1.0f, AudioUtilities::Blend::blend(val1, val2, 0.0f), 0.001f);
            Assert::AreEqual(0.0f, AudioUtilities::Blend::blend(val1, val2, 0.5f), 0.001f);
            Assert::AreEqual(1.0f, AudioUtilities::Blend::blend(val1, val2, 1.0f), 0.001f);
        }
        TEST_METHOD(TestBipolarBlend){
            float val1 = -1.0f;
            float val2 = 1.0f;
            Assert::AreEqual(-1.0f, AudioUtilities::Blend::bipolarBlend(val1, val2, -1.0f), 0.001f);
            Assert::AreEqual(0.0f, AudioUtilities::Blend::bipolarBlend(val1, val2, 0.0f), 0.001f);
            Assert::AreEqual(1.0f, AudioUtilities::Blend::bipolarBlend(val1, val2, 1.0f), 0.001f);
        }
};
}
