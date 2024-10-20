#pragma once

#pragma once
#include "KeyValueStore.h"
#include "KeyValueStoreFile.h"
#include <string>

namespace SquirrelDB::Factory {
	std::vector<std::string> listAllDatabases();
}

namespace SquirrelDB::Factory::KVStore
{
	KeyValueStore createEmptyDatabase(const std::string& dbname);
	KeyValueStore loadExistingDatabase(const std::string& dbname);
}

namespace SquirrelDB::Factory::KVFileStore
{
	KeyValueStoreFile createEmptyDatabase(const std::string& dbname);
	KeyValueStoreFile loadExistingDatabase(const std::string& dbname);
}