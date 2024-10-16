#pragma once

#pragma once
#include "Database.h"
#include <string>


namespace SquirrelDB
{
	Database createEmptyDatabase(const std::string& dbname);
	Database loadExistingDatabase(const std::string& dbname);
	std::vector<std::string> listAllDatabases();
}