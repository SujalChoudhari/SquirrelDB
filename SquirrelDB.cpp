#include <iostream>
#include "LibSquirrel.h"

int main()
{
    std::cout << "Hello World!\n";
    
    SquirrelDB::Database db = SquirrelDB::createEmptyDatabase("newDB");
    db.setValue("test_value_1", "value_to_the_given_key"  );

    std::cout << db.getValue("test_value_1", "nono");
	return 0;
}
