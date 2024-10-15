#include <iostream>

#include "pch.h"
#include "framework.h"
#include "include/LibSquirrel.h"
#include "include/Database.h"
#include "iostream"
#include "include/constants.h"
namespace SquirrelDB {

	Database createEmptyDatabase(const std::string& dbname)
	{
		// if base dir not exist create it
		if (!std::filesystem::exists(BASE_DIR)) {
			std::filesystem::create_directory(BASE_DIR);
		}

		// create a folder for a new db
		const std::filesystem::path dbPath = std::filesystem::path(BASE_DIR) / dbname;

		// create the folder if not exist, if exist throw an error
		if (!std::filesystem::exists(dbPath)) {
			std::filesystem::create_directory(dbPath);
		}
		else {
			//throw std::runtime_error("Database already exist");
		}

		return Database(dbname, dbPath.string());
	}

	Database loadExistingDatabase(const std::string& dbname)
	{
		const std::vector<std::string> list_of_databases = listAllDatabases();
		if (std::find(list_of_databases.begin(), list_of_databases.end(), dbname) == list_of_databases.end()) {
			std::cout << "Database '" << dbname << "' not found" << std::endl;
			std::cout << "Creating Database '" << dbname << "'" << std::endl;
			return createEmptyDatabase(dbname);
		}

		return Database(dbname, BASE_DIR);
	}

	std::vector<std::string> listAllDatabases() {
		// make a list of all the folders in the base dir
		std::vector<std::string> list_of_databases;
		for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(BASE_DIR))) {
			if (entry.is_directory()) {
				list_of_databases.push_back(entry.path().filename().string());
			}
		}
		return list_of_databases;

	}


}