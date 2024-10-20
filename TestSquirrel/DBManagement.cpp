#include "pch.h"
#include "CppUnitTest.h"
#include "SquirrelDB.h"
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

		TEST_METHOD(Create_Empty)
		{
			std::string dbName = "dbsss";

			SquirrelDB::KeyValueStore db = SquirrelDB::Factory::KVStore::createEmptyDatabase(dbName);

			// new folder exists
			Assert::IsTrue(std::filesystem::exists(db.getDirectory()));

			// new folder is empty
			Assert::IsTrue(std::filesystem::is_empty(db.getDirectory()));

			// remove the folder
			db.completelyDestroyDatabase();

			// does not exits
			Assert::IsFalse(std::filesystem::exists(db.getDirectory()));
		}
	};

	/// Story:
	///		[Who]	As a database user
	///		[What]	Load an existing database
	///		[Value] Use the mentioned database after creation
	TEST_CLASS(Load_DB) {
public:
	Load_DB() {
		// create db
		SquirrelDB::Factory::KVStore::createEmptyDatabase("load_db_test_db");
	}

	TEST_METHOD(Load_Existing_DB) {
		// load db
		SquirrelDB::KeyValueStore db = SquirrelDB::Factory::KVStore::loadExistingDatabase("load_db_test_db");

		// db should have valid disk entry
		Assert::IsTrue(std::filesystem::exists(db.getDirectory()));

		db.completelyDestroyDatabase();
	}
	};


	/// Story:
	///		[Who] As an Admin
	///		[What] I would like to see what databases already exists
	///		[value] Proper knowledge of the existing databases
	TEST_CLASS(List_ALL_DB) {

		TEST_METHOD(List_ALL_DB_Test) {
			SquirrelDB::KeyValueStore db = SquirrelDB::Factory::KVStore::loadExistingDatabase("get_all_test_db");

			std::vector<std::string> listOfDatabase = SquirrelDB::Factory::listAllDatabases();

			Assert::IsTrue(listOfDatabase.size() > 0);
			db.completelyDestroyDatabase();
		}
	};
}
