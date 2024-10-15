#include "pch.h"
#include "include/Database.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace SquirrelDB
{
	Database::Database(const std::string& dbName, const std::string& fullPath)
		:mDatabaseName(dbName), mDirectory(std::filesystem::path(fullPath))
	{
	}

	std::filesystem::path Database::getDirectory(void) const
	{
		return mDirectory;
	}

	std::string Database::getDatabaseName(void) const
	{
		return mDatabaseName;
	}

	std::string Database::getValue(std::string key, std::string defaultValue) const
	{
		// check if file exists
		if (std::filesystem::exists(mDirectory / std::filesystem::path(key + KV_EXTENSION))) {

			// open the file
			std::ifstream file;
			file.open(mDirectory / std::filesystem::path(key + KV_EXTENSION));

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

	void Database::setValue(std::string key, std::string value) const
	{
		// create a entry in the folder as .kv
		std::ofstream file;
		file.open(mDirectory / (key + KV_EXTENSION), std::ios::out | std::ios::trunc);
		file << value;
		file.close();
	}

	Database Database::createNewEmptyDatabase(const std::string dbName)
	{
		// if base dir not exist create it
		if (!std::filesystem::exists(BASE_DIR)) {
			std::filesystem::create_directory(BASE_DIR);
		}

		// create a folder for a new db
		const std::filesystem::path dbPath = std::filesystem::path(BASE_DIR) / dbName;

		// create the folder if not exist, if exist throw an error
		if (!std::filesystem::exists(dbPath)) {
			std::filesystem::create_directory(dbPath);
		}
		else {
			//throw std::runtime_error("Database already exist");
		}

		return Database(dbName, dbPath.string());
	}

	Database Database::loadExistingDatabase(const std::string dbName) {

		const std::vector<std::string> list_of_databases = getAllDatabase();
		if (std::find(list_of_databases.begin(), list_of_databases.end(), dbName) == list_of_databases.end()) {
			std::cout << "Database '" << dbName << "' not found" << std::endl;
			std::cout << "Creating Database '" << dbName << "'" << std::endl;
			return createNewEmptyDatabase(dbName);
		}

		return Database(dbName, BASE_DIR);
	}

	std::vector<std::string> Database::getAllDatabase()
	{
		// make a list of all the folders in the base dir
		std::vector<std::string> list_of_databases;
		for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(BASE_DIR))) {
			if (entry.is_directory()) {
				list_of_databases.push_back(entry.path().filename().string());
			}
		}
		return list_of_databases;
	}

	void Database::completelyDestroyDatabase(void) const
	{
		if (std::filesystem::exists(mDirectory)) {
			std::filesystem::remove_all(mDirectory);
		}
	}
}