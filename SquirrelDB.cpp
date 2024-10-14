#include <iostream>
#include "LibSquirrel.h"
#include "cxxopts.h"

typedef std::shared_ptr<cxxopts::Options> OptionPtr;

/// <summary>
/// Print the Help Menu
/// </summary>
/// <param name="options"> Option menu to use while printing help</param>
static void printHelp(const OptionPtr& options) {
	std::cout << options->help() << std::endl;
}

/// <summary>
/// Add options to the cli
/// </summary>
/// <param name="options">Shared Options Pointer</param>
static void addOptions(const OptionPtr& options) {
	options->add_options()
		("h,help", "Show this menu")
		("c,create", "Create a new database")
		("d,destroy", "Delete the database")
		("s,set", "Set a key-value pair")
		("g,get", "Get a key-value pair")
		("n,name", "Database name (required)", cxxopts::value<std::string>())
		("k,key", "Key to set/get", cxxopts::value<std::string>())
		("v,value", "Value to set", cxxopts::value<std::string>());
}

static void handleCreate(const cxxopts::ParseResult& result) {
	if (result.count("name")) {
		std::string dbName = result["name"].as<std::string>();
		std::cout << "Creating database: " << dbName << std::endl;
		SquirrelDB::createEmptyDatabase(dbName);
	}
	else {
		std::cerr << "Error: Please specify a database name using --name [name]." << std::endl;
	}
}

static void handleDestroy(const cxxopts::ParseResult& result) {
	if (result.count("name")) {
		std::string dbName = result["name"].as<std::string>();
		std::cout << "Destroying database: " << dbName << std::endl;
		SquirrelDB::createEmptyDatabase(dbName).completelyDestroyDatabase();
	}
	else {
		std::cerr << "Error: Please specify a database name using --name [name]." << std::endl;
	}
}

/// <summary>
/// Interpret the given arguments
/// </summary>
/// <param name="result">Result from the parsing</param>
/// <param name="options">Options for using the help menu</param>
static void interpret(const cxxopts::ParseResult& result, const OptionPtr& options) {
	if (result.count("create")) {
		handleCreate(result);
	}
	else if (result.count("destroy")) {
		handleDestroy(result);
	}
	else {
		printHelp(options);
	}
}

int main(int argc, char* argv[]) {
	OptionPtr options = std::make_shared<cxxopts::Options>("sqrldb", "Database CLI tool for SquirrelDB");
	addOptions(options);

	try {

		cxxopts::ParseResult result = options->parse(argc, argv);
		interpret(result, options);
	}
	catch (const std::exception& ex) {

		std::cerr << "Error parsing options: " << ex.what() << std::endl;
		printHelp(options);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
