#pragma once
#include "KeyValueStore.h"
#include "KeyValueStoreFile.h"
#include <string>
#include <iostream>
#include "constants.h"

namespace SquirrelDB::Factory {
	std::vector<std::string> listAllDatabases();
}

namespace SquirrelDB::Factory::KVStore
{
	template<typename K, typename V>
	KeyValueStore<K, V>  createEmptyDatabase(const std::string& dbname);

	template<typename K, typename V>
	KeyValueStore<K, V>  loadExistingDatabase(const std::string& dbname);
}

namespace SquirrelDB::Factory::KVFileStore
{
	KeyValueStoreFile createEmptyDatabase(const std::string& dbname);
	KeyValueStoreFile loadExistingDatabase(const std::string& dbname);
}



namespace SquirrelDB::Factory::KVStore {

	template<typename K, typename V>
	KeyValueStore<K, V> createEmptyDatabase(const std::string& dbname)
	{
		if (!std::filesystem::exists(BASE_DIR)) {
			std::filesystem::create_directory(BASE_DIR);
		}

		const std::filesystem::path dbPath = std::filesystem::path(BASE_DIR) / dbname;

		if (!std::filesystem::exists(dbPath)) {
			std::filesystem::create_directory(dbPath);
		}

		return KeyValueStore<K, V>(dbname, dbPath.string());
	}

	template<typename K, typename V>
	KeyValueStore<K, V> loadExistingDatabase(const std::string& dbname)
	{
		const std::vector<std::string> list_of_databases = listAllDatabases();
		if (std::find(list_of_databases.begin(), list_of_databases.end(), dbname) == list_of_databases.end()) {
			std::cout << "Database '" << dbname << "' not found" << std::endl;
			std::cout << "Creating Database '" << dbname << "'" << std::endl;
			return createEmptyDatabase<K, V>(dbname);
		}

		return KeyValueStore<K, V>(dbname, (std::filesystem::path(BASE_DIR) / dbname).string());
	}
}
