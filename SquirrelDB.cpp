#include <iostream>
#include "LibSquirrel.h"

int main()
{
    std::cout << "Hello World!\n";
    
    SquirrelDB::Database db = SquirrelDB::createEmptyDatabase("newDB");

	return 0;
}
