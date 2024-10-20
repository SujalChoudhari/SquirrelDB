#pragma once

#pragma once
#include "KeyValueStore.h"
#include <string>


namespace SquirrelDB
{
	KeyValueStore createEmptyDatabase(const std::string& dbname);
	KeyValueStore loadExistingDatabase(const std::string& dbname);
	std::vector<std::string> listAllDatabases();
}