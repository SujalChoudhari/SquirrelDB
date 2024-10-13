#include <iostream>

#include "pch.h"
#include "framework.h"
#include "LibSquirrel.h"
#include "Database.h"


SquirrelDB::Database SquirrelDB::createEmptyDatabase(const std::string& dbname)
{
	return SquirrelDB::Database::createNewEmptyDatabase(dbname);
}
