#include "pch.h"
#include "CppUnitTest.h"
#include "LibSquirrel.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBManagement
{
	TEST_CLASS(Create_DB)
	{
	public:

		TEST_METHOD(Create_Empty)
		{
			std::string dbName = "testDB";

			SquirrelDB::Database db = SquirrelDB::createEmptyDatabase(dbName);

			// new folder exists
			Assert::IsTrue(std::filesystem::exists(db.getDirectory()));

			// new folder is empty
			Assert::IsTrue(std::filesystem::is_empty(db.getDirectory()));

			// remove the folder
			std::filesystem::remove(db.getDirectory());
		}
	};
}
