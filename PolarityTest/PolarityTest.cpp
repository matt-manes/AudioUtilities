#include "../AudioUtilities/Polarity.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PolarityTest {
TEST_CLASS(PolarityTest){
    public :

        TEST_METHOD(TestBipolarToUnipolar){
            Assert::AreEqual(0.0f, AudioUtilities::Polarity::bipolarToUnipolar(-1.0f), 0.001f);
            Assert::AreEqual(0.25f, AudioUtilities::Polarity::bipolarToUnipolar(-0.5f), 0.001f);
            Assert::AreEqual(0.5f, AudioUtilities::Polarity::bipolarToUnipolar(0.0f), 0.001f);
            Assert::AreEqual(0.75f, AudioUtilities::Polarity::bipolarToUnipolar(0.5f), 0.001f);
            Assert::AreEqual(1.0f, AudioUtilities::Polarity::bipolarToUnipolar(1.0f), 0.001f);
        }

        TEST_METHOD(TestUnipolarToBipolar){
            Assert::AreEqual(-1.0f, AudioUtilities::Polarity::unipolarToBipolar(0.0f), 0.001f);
            Assert::AreEqual(-0.5f, AudioUtilities::Polarity::unipolarToBipolar(0.25f), 0.001f);
            Assert::AreEqual(0.0f, AudioUtilities::Polarity::unipolarToBipolar(0.5f), 0.001f);
            Assert::AreEqual(0.5f, AudioUtilities::Polarity::unipolarToBipolar(0.75f), 0.001f);
            Assert::AreEqual(1.0f, AudioUtilities::Polarity::unipolarToBipolar(1.0f), 0.001f);
        }
};
}
