#include "pch.h"
#include "Database.h"
#include <filesystem>

namespace SquirrelDB
{
	Database::Database(const std::string& dbName, const std::string& fullPath)
		:mDatabaseName(dbName), mDirectory(std::filesystem::path(fullPath))
	{
	}

	std::filesystem::path Database::getDirectory(void)
	{
		return mDirectory;
	}

	std::string Database::getDatabaseName(void)
	{
		return mDatabaseName;
	}

	Database Database::createNewEmptyDatabase(const std::string dbName)
	{
		const std::filesystem::path BASE_DIR = "./squirreldb";
		// if base dir not exist create it
		if (!std::filesystem::exists(BASE_DIR)) {
			std::filesystem::create_directory(BASE_DIR);
		}

		// create a folder for a new db
		const std::filesystem::path dbPath = BASE_DIR / dbName;

		// create the folder if not exist, if exist throw an error
		if (!std::filesystem::exists(dbPath)) {
			std::filesystem::create_directory(dbPath);
		}
		else {
			throw std::runtime_error("Database already exist");
		}

		return Database(dbName, dbPath.string());
	}
}