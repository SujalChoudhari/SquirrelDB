#include "pch.h"
#include "Database.h"
#include <filesystem>
#include <fstream>

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

	std::string Database::getValue(std::string key, std::string defaultValue)
	{
		// check if file exists
		if (std::filesystem::exists(mDirectory / std::filesystem::path(key + "_string" + ".kv"))) {

			// open the file
			std::ifstream file;
			file.open(mDirectory / std::filesystem::path(key + "_string" + ".kv"));

			// read the file
			std::string value;
			file.seekg(0, std::ios::end);
			value.reserve(file.tellg());
			file.seekg(0, std::ios::beg);
			value.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			return value;
		}
		else {
			return defaultValue;
		}
	}

	void Database::setValue(std::string key, std::string value)
	{
		// create a entry in the folder as .kv
		std::ofstream file;
		file.open(mDirectory / (key + "_string" + ".kv"), std::ios::out | std::ios::trunc);
		file << value;
		file.close();
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
			//throw std::runtime_error("Database already exist");
		}

		return Database(dbName, dbPath.string());
	}
}