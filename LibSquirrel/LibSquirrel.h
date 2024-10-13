#pragma once
#include "Database.h"
#include <string>
namespace SquirrelDB
{
	Database createEmptyDatabase(const std::string& dbname);
}