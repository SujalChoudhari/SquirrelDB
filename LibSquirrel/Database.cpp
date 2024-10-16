#include "pch.h"
#include "include/Database.h"
#include "include/constants.h"
#include <filesystem>
#include <fstream>
#include <iostream>


/// <summary>
/// Definition of class DatabaseImplementation
/// </summary>
namespace SquirrelDB
{
	// private to Library
	class Database::DatabaseImpl : public IDatabase
	{

	public:
		DatabaseImpl(const std::string& dbName, const std::string& fullPath);
		std::filesystem::path	getDirectory(void) const;
		std::string				getDatabaseName(void) const;
		std::string				getValue(std::string key, std::string defaultValue) const;
		void					setValue(std::string key, std::string value) const;
		void					completelyDestroyDatabase(void) const;

	private:
		std::string				m_DatabaseName;
		std::filesystem::path	m_Directory;
	};
}



/// <summary>
/// Database Implementations
/// </summary>
namespace SquirrelDB
{

	Database::Database(const std::string& dbName, const std::string& fullPath)
	{
		m_Impl = std::make_unique<DatabaseImpl>(dbName, fullPath);
	}

	Database::~Database()
	{
		// unique_ptr will automatically delete m_Impl when Database is destroyed.
		// No need to manually do anything here.
	}


	std::filesystem::path Database::getDirectory(void) const
	{
		return m_Impl->getDirectory();
	}

	std::string Database::getDatabaseName(void) const
	{
		return m_Impl->getDatabaseName();
	}

	std::string Database::getValue(std::string key, std::string defaultValue) const
	{
		// check if file exists
		if (std::filesystem::exists(m_Impl->getDirectory() / std::filesystem::path(key + KV_EXTENSION))) {

			// open the file
			std::ifstream file;
			file.open(m_Impl->getDirectory() / std::filesystem::path(key + KV_EXTENSION));

			// read the file
			std::string value;
			file.seekg(0, std::ios::end);
			value.reserve(file.tellg());
			file.seekg(0, std::ios::beg);
			value.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			return value;
		}
		else {
			return defaultValue;
		}
	}

	void Database::setValue(std::string key, std::string value) const
	{
		// create a entry in the folder as .kv
		std::ofstream file;
		file.open(m_Impl->getDirectory() / (key + KV_EXTENSION), std::ios::out | std::ios::trunc);
		file << value;
		file.close();
	}

	void Database::completelyDestroyDatabase(void) const
	{
		if (std::filesystem::exists(m_Impl->getDirectory())) {
			std::filesystem::remove_all(m_Impl->getDirectory());
		}
	}
}


/// <summary>
/// DatabaseImpl Implementation
/// </summary>
namespace SquirrelDB
{

	Database::DatabaseImpl::DatabaseImpl(const std::string& dbName, const std::string& fullPath)
		:m_DatabaseName(dbName), m_Directory(std::filesystem::path(fullPath))
	{
		;
	}

	std::filesystem::path Database::DatabaseImpl::getDirectory(void) const
	{
		return m_Directory;
	}

	std::string Database::DatabaseImpl::getDatabaseName(void) const
	{
		return m_DatabaseName;
	}

	std::string Database::DatabaseImpl::getValue(std::string key, std::string defaultValue) const
	{
		// check if file exists
		if (std::filesystem::exists(m_Directory / std::filesystem::path(key + KV_EXTENSION))) {

			// open the file
			std::ifstream file;
			file.open(m_Directory / std::filesystem::path(key + KV_EXTENSION));

			// read the file
			std::string value;
			file.seekg(0, std::ios::end);
			value.reserve(file.tellg());
			file.seekg(0, std::ios::beg);
			value.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			return value;
		}
		else {
			return defaultValue;
		}
	}

	void Database::DatabaseImpl::setValue(std::string key, std::string value) const
	{
		// create a entry in the folder as .kv
		std::ofstream file;
		file.open(m_Directory / (key + KV_EXTENSION), std::ios::out | std::ios::trunc);
		file << value;
		file.close();
	}

	void Database::DatabaseImpl::completelyDestroyDatabase(void) const
	{
		if (std::filesystem::exists(m_Directory)) {
			std::filesystem::remove_all(m_Directory);
		}
	}
}

