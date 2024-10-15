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
		virtual void					setValue(std::string key, std::string value)		const = 0;
		virtual void					completelyDestroyDatabase(void)						const = 0;

	public:
		virtual ~IDatabase() = default;
	};
}


namespace SquirrelDB {
	class Database : public IDatabase {

	public:
		class DatabaseImpl;
		Database(const std::string& dbName, const std::string& fullPath);
		~Database();

		std::filesystem::path			getDirectory(void)									const;
		std::string						getDatabaseName(void)								const;
		std::string						getValue(std::string key, std::string defaultValue) const;
		void							setValue(std::string key, std::string value)		const;
		void							completelyDestroyDatabase(void)						const;

	private:
		std::shared_ptr<DatabaseImpl>	m_Impl;
	};
}