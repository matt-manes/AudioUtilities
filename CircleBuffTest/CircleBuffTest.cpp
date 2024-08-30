#include "../AudioUtilities/CircleBuff.h"
#include "../AudioUtilities/Range.h"
#include "CppUnitTest.h"

// clang-format off

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AudioUtilities;

namespace CircleBuffTest
{
    TEST_CLASS(CircleBuffTest)
    {
      public:

        // Verify the buffer is size 10 and filled with values 0->9 in order,
        // unless `verifyFlush` is `true`, in which case verify all values are 0
        void verifyBuffer(CircleBuff::CircleBuff<int> &buff,
                          bool verifyFlush = false)
        {
            Assert::AreEqual(10, buff.size());
            for (int i = 0; i < buff.size(); ++i)
            {
                if (verifyFlush) {Assert::AreEqual(0, buff[i]);}
                else {Assert::AreEqual(i, buff[i]);}
            }
        }

        void verifyAndFlush(CircleBuff::CircleBuff<int> &buff)
        {
            verifyBuffer(buff);
            buff.flush();
            verifyBuffer(buff, true);
        }

        TEST_METHOD(WriteTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            verifyBuffer(buff, true);
            // First overload: give value, internal write increment
            // (buff.size() * 2 is to ensure proper index wrapping
            for (int i = 0; i < buff.size()*2; ++i)
            {
                buff.write(i % buff.size());
            }
            verifyAndFlush(buff);

            // Second overload: give value and manual write index
            for (int i = 0; i < buff.size()*2; ++i)
            {
                buff.write(i % buff.size(), i);  
            }
            verifyAndFlush(buff);

            // Third overload: give value and external Index object
            // `*5` to verify index is set in write function to prevent out of bounds
            Index::Index index(0, buff.size()*5); 
            for (int i = 0; i < buff.size()*2; ++i)
            {
                buff.write(i % buff.size(), index++);  
            }
            verifyAndFlush(buff);
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
            Assert::AreEqual(buff.size() - 1, buff.getWritedex()->getMax());
        }

        TEST_METHOD(NonPrimitiveTypeTest)
        {
            AudioUtilities::CircleBuff::CircleBuff
                <AudioUtilities::Range::Range<int>> buff(10);
            AudioUtilities::Range::Range<int> test;
            for (int i = 0; i < buff.size(); ++i)
            {
                // Assert all values are default
                Assert::IsTrue(test == buff.read(i));
                // Change `stopValue`
                buff.write(AudioUtilities::Range::Range<int>(0,i));
            }
            for (int i = 0; i < buff.size(); ++i)
            {
                test.setStop(i);
                Assert::IsTrue(test == buff.read(i));
            }
            test = AudioUtilities::Range::Range<int>();
            buff.flush();
            // Test flush put them all back to default
            for (int i = 0; i < buff.size(); ++i)
            {
                Assert::IsTrue(test == buff.read(i));
            }
        }

        TEST_METHOD(BracketReadOverloadTest)
        {
            AudioUtilities::CircleBuff::CircleBuff<int> buff(10);
            for (int i = 0; i < buff.size(); ++i)
            {
                buff.write(i);
            }
            Assert::AreEqual(5, buff[5]);
            Assert::AreEqual(5.5f, buff[5.5f]);
            Assert::AreEqual(5.5f, buff[15.5f]);
            float val = buff[AudioUtilities::Index::Index(
                                buff.size() - 1)=5.5f];
            Assert::AreEqual(5.5f, val);
            val = buff[AudioUtilities::Index::Index(
                                buff.size() - 1)=15.5f];
            Assert::AreEqual(5.5f, val);

        }
    };
}
