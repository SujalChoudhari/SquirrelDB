#pragma once
#include <filesystem>

namespace SquirrelDB
{
	class IDatabase
	{
	public:
		virtual std::filesystem::path	getDirectory(void)									const = 0;
		virtual std::string				getDatabaseName(void)								const = 0;
		virtual std::string				getValue(std::string key, std::string defaultValue) const = 0;
		virtual void					setValue(std::string key, std::string value) = 0;
		virtual void					completelyDestroyDatabase(void) = 0;

	public:
		virtual ~IDatabase() = default;
	};
}

