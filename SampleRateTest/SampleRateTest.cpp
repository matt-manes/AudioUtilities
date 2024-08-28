#include "../AudioUtilities/SampleRate.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SampleRateTest {
TEST_CLASS(SampleRateTest){
    public :

        TEST_METHOD(TestConverter){
            AudioUtilities::SampleRate::Converter converter = AudioUtilities::SampleRate::Converter(44100);
            Assert::AreEqual(44100, converter.fromSeconds(1.0f));
            Assert::AreEqual(22050, converter.fromSeconds(0.5f));
            Assert::AreEqual(22050, converter.fromMilliseconds(500));
            Assert::AreEqual(1.0f, converter.toSeconds(44100), 0.000001f);
            Assert::AreEqual(.5f, converter.toSeconds(22050), 0.000001f);
            Assert::AreEqual(500.0f, converter.toMilliseconds(22050), 0.000001f);
        }
};
}
