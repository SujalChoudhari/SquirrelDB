#include "pch.h"
#include "CppUnitTest.h"
#include "LibSquirrel.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBManagement
{
	/// Story:
	///		[Who] DB admin should be able to create an empty database
	///		[What] Each database has a folder for it
	///		[Value] Store data in the database
	TEST_CLASS(Create_DB)
	{
	public:

		/// Algorithm:
		///		1. Create an empty database
		///		2. Check if folder structure exists
		///		3. Remove the folder
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
