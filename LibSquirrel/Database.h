#pragma once
#include <string>
#include <filesystem>

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
		void completelyDestroyDatabase(void) const;

	private:
		std::string mDatabaseName;
		std::filesystem::path mDirectory;


		Database(const std::string& dbName, const std::string& fullPath);
	};
}
