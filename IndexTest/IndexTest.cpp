#include "../AudioUtilities/Index.h"
#include "CppUnitTest.h"
// clang-format off
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IndexTest 
{
TEST_CLASS(IndexTest)
{
    public :

        TEST_METHOD(testInitialState)
		{
			AudioUtilities::Index::Index index = AudioUtilities::Index::Index(1);
			Assert::AreEqual(index.getFull(), 0.0f);
			Assert::AreEqual(index.getLower(), 0);
			Assert::AreEqual(index.getUpper(), 1);
			Assert::AreEqual(index.getDecimal(), 0.0f);
		}

		TEST_METHOD(testSetIndex)
		{
			AudioUtilities::Index::Index index = AudioUtilities::Index::Index(10);
			float val = 5.0f;
			index.setIndex(val);
			Assert::AreEqual(val, index.getFull());
			Assert::AreEqual((int)val, index.getLower());
			Assert::AreEqual((int)val+1, index.getUpper());
			Assert::AreEqual(0.0f, index.getDecimal());
			// Non-zero decimal
			val = 4.2f;
			index.setIndex(val);
			Assert::AreEqual(val, index.getFull());
			Assert::AreEqual((int)val, index.getLower());
			Assert::AreEqual((int)val + 1, index.getUpper());
			Assert::AreEqual(0.2f, index.getDecimal(), 0.1f);
		}

		TEST_METHOD(testIndexWrapping)
		{
			AudioUtilities::Index::Index index = 
				AudioUtilities::Index::Index(AudioUtilities::Range::Range<int>(0, 10));
			// When in max <-> paddedMax region.
			index.setIndex(10.5f);
			Assert::AreEqual(10.5f, index.getFull(), 0.1f);
			Assert::AreEqual(10, index.getLower());
			Assert::AreEqual(index.getMin(), index.getUpper());
			Assert::AreEqual(0.5f, index.getDecimal(), 0.1f);

			// When out of bounds.
			index.setIndex(11.7f);
			Assert::AreEqual(0.7f, index.getFull(), 0.1f);
			Assert::AreEqual(0, index.getLower());
			Assert::AreEqual(1, index.getUpper());
			Assert::AreEqual(0.7f,index.getDecimal(), 0.1f);

		}

		TEST_METHOD(testSetMin)
		{
			AudioUtilities::Index::Index index = AudioUtilities::Index::Index(10);
			Assert::AreEqual(0.0f, index.getFull(), 0.1f);
			index.setMin(5);
			Assert::AreEqual(5.0f, index.getFull(), 0.1f);
			Assert::AreEqual(6, index.getUpper());
			Assert::AreEqual(5, index.getLower());
			Assert::AreEqual(0.0f, index.getDecimal(), 0.1f);
			index.setIndex(12.2f);
			Assert::AreEqual(5.2f, index.getFull(), 0.1f);
			Assert::AreEqual(6, index.getUpper());
			Assert::AreEqual(5, index.getLower());
			Assert::AreEqual(0.2f, index.getDecimal(), 0.1f);
			index.setMin(1);
			Assert::AreEqual(5.2f, index.getFull(), 0.1f);
		}

		TEST_METHOD(testOperators)
		{
			AudioUtilities::Index::Index index = AudioUtilities::Index::Index(10);
			index = 2;
			Assert::AreEqual(2.0f, index.getFull(), 0.1f);
			index++;
			Assert::AreEqual(3.0f, index.getFull(), 0.1f);
			Assert::AreEqual(3, index.getLower());
			Assert::AreEqual(4, index.getUpper());
			Assert::AreEqual(0.0f, index.getDecimal(), 0.1f);
			index--;
			Assert::AreEqual(2.0f, index.getFull(), 0.1f);
			Assert::AreEqual(2, index.getLower());
			Assert::AreEqual(3, index.getUpper());
			Assert::AreEqual(0.0f, index.getDecimal(), 0.1f);
			// urnary ops use the binary ops, so testing them should count as both
			index += 3.3f;
			Assert::AreEqual(5.3f, index.getFull(), 0.1f);
			Assert::AreEqual(5, index.getLower());
			Assert::AreEqual(6, index.getUpper());
			Assert::AreEqual(0.3f, index.getDecimal(), 0.1f);
			index -= 3.3f;
			Assert::AreEqual(2.0f, index.getFull(), 0.1f);
			index *= 2;
			Assert::AreEqual(4.0f, index.getFull(), 0.1f);
			index /= 2;
			Assert::AreEqual(2.0f, index.getFull(), 0.1f);
			// chain - ((2 * 3) + 2) * 3 / 2 = 12 which should be full = 1
			index = ((index * 3) + 2) * 3 / 2;
			Assert::AreEqual(1.0f, index.getFull(), 0.1f);
		}
};
}
