#pragma once
#include <filesystem>

/// <summary>
/// Database extends IDatabase.
/// And have a pointer to the DatabaseImpl
/// 
/// DatabaseImpl is the actual implementation of the database,
/// it is hidden from the user, User can only see the database class,
/// the interface but not the Implementation.
/// 
/// </summary>

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


namespace SquirrelDB {
	class Database : public IDatabase {

	public:
		Database(const std::string& dbName, const std::string& fullPath);
		~Database();

		class DatabaseImpl;
		std::filesystem::path			getDirectory(void)									const;
		std::string						getDatabaseName(void)								const;
		std::string						getValue(std::string key, std::string defaultValue) const;
		void							setValue(std::string key, std::string value);
		void							completelyDestroyDatabase(void);

	private:
		std::shared_ptr<DatabaseImpl>	m_Impl;
	};
}