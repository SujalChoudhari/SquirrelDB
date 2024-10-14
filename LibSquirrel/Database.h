#pragma once
#include <string>
#include <filesystem>

#define BASE_DIR "./squirreldb"
#define KV_EXTENSION "_string.kv"

namespace SquirrelDB
{

	class Database
	{
	public:
		std::filesystem::path getDirectory(void) const;
		std::string getDatabaseName(void) const;

	public:
		std::string getValue(std::string key, std::string defaultValue) const;
		void setValue(std::string key, std::string value) const;

		static Database createNewEmptyDatabase(const std::string dbName);
		static Database loadExistingDatabase(const std::string dbName);
		static std::vector<std::string> getAllDatabase();
		void completelyDestroyDatabase(void) const;

	private:
		std::string mDatabaseName;
		std::filesystem::path mDirectory;


		Database(const std::string& dbName, const std::string& fullPath);
	};
}
