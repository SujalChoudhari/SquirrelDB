#include "pch.h"
#include "CppUnitTest.h"
#include "LibSquirrel.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSquirrel
{
	TEST_CLASS(TestSquirrel)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			fnLibSquirrel();
		}
	};
}
