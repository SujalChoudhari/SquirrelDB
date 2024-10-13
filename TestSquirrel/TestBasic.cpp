#include "pch.h"
#include "CppUnitTest.h"
#include "LibSquirrel.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBasic
{
	TEST_CLASS(Test_For_Testing_TestFrameworks)
	{
	public:
		
		TEST_METHOD(Are_Equal)
		{
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(Are_Not_Equal) {
			Assert::AreNotEqual(1, 2);
		}
	};
}
