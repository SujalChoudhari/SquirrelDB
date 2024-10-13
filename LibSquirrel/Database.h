#pragma once
#include <string>
#include <filesystem>

namespace SquirrelDB
{

	class Database
	{
	public:
		std::filesystem::path getDirectory(void);
		std::string getDatabaseName(void);

		static Database createNewEmptyDatabase(const std::string dbName);

	private:
		std::string mDatabaseName;
		std::filesystem::path mDirectory;


		Database(const std::string& dbName, const std::string& fullPath);
	};
}
