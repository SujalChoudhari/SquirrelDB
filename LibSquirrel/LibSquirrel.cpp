#include <iostream>

#include "pch.h"
#include "framework.h"
#include "include/LibSquirrel.h"
#include "include/Database.h"


SquirrelDB::Database SquirrelDB::createEmptyDatabase(const std::string& dbname)
{
	return SquirrelDB::Database::createNewEmptyDatabase(dbname);
}

SquirrelDB::Database SquirrelDB::loadExistingDatabase(const std::string& dbname)
{
	return SquirrelDB::Database::loadExistingDatabase(dbname);
}

std::vector<std::string> SquirrelDB::listAllDatabases() {
	return SquirrelDB::Database::getAllDatabase();
}
