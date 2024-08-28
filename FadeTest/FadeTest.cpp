#include "../AudioUtilities/Fade.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FadeTest
{
TEST_CLASS(FadeTest)
{
    public :

        TEST_METHOD(TestFadeIn)
        {
            AudioUtilities::Fade::Fade fade = AudioUtilities::Fade::Fade(100, 1000);

            float out = 0.0f;

            for (int i = 0; i < 1000; ++i)
            {
                out = fade.apply(i);
                if (i < 100) { Assert::AreEqual(0.0f, out, 0.00001f); }
                if (i == 100) { fade.start(); }
                // Ramping up should have out lagging behind i
                if (fade.isActive()) { Assert::IsTrue(out < i); }
                if (fade.isFinished()) { Assert::AreEqual((float)i, out, 0.00001f); }
                fade.tick();
            }
        }

        TEST_METHOD(TestFadeOut)
        {
            AudioUtilities::Fade::Fade fade = AudioUtilities::Fade::Fade(
              100, 1000, AudioUtilities::Fade::Direction::Out
            );
            float out = 0.0f;
            for (int i = 0; i < 1000; ++i)
            {
                out = fade.apply(i);
                if (i < 100) { Assert::AreEqual((float)i, out, 0.00001f); }
                if (i == 100) { fade.start(); }
                // Ramping down should have out lagging behind i
                else if (fade.isActive()) { Assert::IsTrue(out < i); }
                if (fade.isFinished()) { Assert::AreEqual(0.0f, out, 0.00001f); }
                fade.tick();
            }
        }
};
}// namespace FadeTest
