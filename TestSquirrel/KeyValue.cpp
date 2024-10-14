#include "pch.h"
#include "CppUnitTest.h"
#include "LibSquirrel.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KeyValuePair
{
	/// Story:
	///		[Who] As a db user,
	///		[What]  I would like to store key value pairs.
	///		[Value] Persistent data for later use.
	TEST_CLASS(KeyValuePairDB)
	{
	private:
		std::string mDbName = "kv_check_db";
		std::shared_ptr<SquirrelDB::Database> mDb;
	public:

		KeyValuePairDB() {
			Create_KV_Database();
		}

		~KeyValuePairDB() {
			mDb->completelyDestroyDatabase();
		}

		TEST_METHOD(Create_KV_Database) {
			mDb = std::make_shared<SquirrelDB::Database>(SquirrelDB::Database::createNewEmptyDatabase(mDbName));
		}

		TEST_METHOD(Check_Already_Set_Value)
		{
			std::string key = "test_value_1";
			std::string value = "value_to_the_given_key";

			mDb->setValue(key, value);

			Assert::IsTrue(value == mDb->getValue(key, "none"));
		}

		TEST_METHOD(Check_Unset_Set_Value_Default_Return)
		{
			std::string key = "test_value_2";
			std::string value = "value_to_the_given_key2";

			Assert::IsTrue(value == mDb->getValue(key, "value_to_the_given_key2"));
		}

		TEST_METHOD(Check_Faulty_Default_Return)
		{
			std::string key = "test_value_3";
			std::string value = "value_to_the_given_key3";

			Assert::IsTrue(value != mDb->getValue(key, "value_to_the_given_keyn"));
		}
	};
}
