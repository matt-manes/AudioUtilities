#include "../AudioUtilities/CircleBuff.h"
#include "../AudioUtilities/Range.h"
#include "CppUnitTest.h"

// clang-format off

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircleBuffTest
{
    TEST_CLASS(CircleBuffTest)
    {
      public:

        TEST_METHOD(BuffTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            Assert::AreEqual(10, buff.size());
            for (int i = 0; i < buff.size(); ++i)
            {
                buff.write(i);
            }
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::AreEqual(i, buff.read(i));
            }
            for (int i = 0; i < buff.size(); ++i)
            {
                buff.write(10+i);
            }
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::AreEqual(10+i, buff.read(i));
            }
        }

        TEST_METHOD(FlushTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            for (int i = 0; i < buff.size(); ++i)
            {
                buff.write(i);
            }
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::AreEqual(i, buff.read(i));
            }
            buff.flush();
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::AreEqual(0, buff.read(i));
            }
        }

        TEST_METHOD(WrapTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            // Basically if there no errors this passes 
            // because our write index properly wrapped
            for (int i = 0; i < 2*buff.size(); ++i)
            {
                buff.write(i);
            }
        }

        TEST_METHOD(ResizeTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            for (int i = 0; i < buff.size() * 1000; ++i)
            {
                buff.write(i);
            }
            Assert::AreEqual(10, buff.size());
            buff.resize(100);
            Assert::AreEqual(100, buff.size());
            // Test if writedex max value properly upated
            for (int i = 0; i < buff.size() * 1000; ++i)
            {
                buff.write(i);
            }
        }

        TEST_METHOD(NonPrimitiveTypeTest)
        {
            AudioUtilities::CircleBuff::CircleBuff
                <AudioUtilities::Range::Range<int>> buff(10);
            AudioUtilities::Range::Range<int> test;
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::IsTrue(test == buff.read(i));
                buff.write(AudioUtilities::Range::Range<int>(0,i));
            }
            for (int i = 0; i < buff.size(); ++i)
            {
                test.setStop(i);
                Assert::IsTrue(test == buff.read(i));
            }
            test = AudioUtilities::Range::Range<int>();
            buff.flush();
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::IsTrue(test == buff.read(i));
            }
        }

        TEST_METHOD(BracketOverloadTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            for (int i = 0; i < buff.size(); ++i)
            {
                buff.write(i);
            }
            Assert::AreEqual(5, buff[5]);
            Assert::AreEqual(5.5f, buff[5.5f]);
            Assert::AreEqual(5.5f, buff[16.5f]);
            float val = buff[AudioUtilities::Index::Index(
                                buff.size())=5.5f];
            Assert::AreEqual(5.5f, val);
            val = buff[AudioUtilities::Index::Index(
                                buff.size())=16.5f];
            Assert::AreEqual(5.5f, val);

        }
    };
}
