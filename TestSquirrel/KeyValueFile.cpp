#include "pch.h"
#include "CppUnitTest.h"
#include "SquirrelDB.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KeyValueFilePair
{
	/// Story:
	///		[Who] As a db user,
	///		[What]  I would like to store key value pairs.
	///		[Value] Persistent data for later use.
	TEST_CLASS(KeyValueFilePairDB)
	{
	private:
		std::string mDbName = "kvf_check_db";
		std::shared_ptr<SquirrelDB::KeyValueStoreFile> mDb;
	public:

		KeyValueFilePairDB() {
			Create_KVF_Database();
		}

		~KeyValueFilePairDB() {
			mDb->completelyDestroyDatabase();
		}

		TEST_METHOD(Create_KVF_Database) {
			mDb = std::make_shared<SquirrelDB::KeyValueStoreFile>(SquirrelDB::Factory::KVFileStore::createEmptyDatabase(mDbName));
		}

		TEST_METHOD(Check_Already_Set_Value_In_File)
		{
			std::string key = "test_value_1k";
			std::string value = "value2_to_the_given_key";

			mDb->setValue(key, value);

			Assert::IsTrue(value == mDb->getValue(key, "none"));
		}

		TEST_METHOD(Check_Unset_Set_Value_Default_Return)
		{
			std::string key = "test_value_2k";
			std::string value = "value_to_the_given_key2";

			Assert::IsTrue(value == mDb->getValue(key, "value_to_the_given_key2"));
		}

		TEST_METHOD(Check_Faulty_Default_Return)
		{
			std::string key = "test_value_3k";
			std::string value = "value_to_the_given_key4";

			Assert::IsTrue(value != mDb->getValue(key, "value_to_the_given_key5"));
		}
	};
}
