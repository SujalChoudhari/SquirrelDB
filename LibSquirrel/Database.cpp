#include "pch.h"
#include "include/Database.h"
#include "include/constants.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>
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
		void					setValue(std::string key, std::string value);
		void					completelyDestroyDatabase(void);

	private:
		std::string				m_DatabaseName;
		std::filesystem::path	m_Directory;
		std::unordered_map<std::string, std::string> m_KeyValue_Store;
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
		return m_Impl->getValue(key, defaultValue);
	}

	void Database::setValue(std::string key, std::string value)
	{
		return m_Impl->setValue(key, value);

	}

	void Database::completelyDestroyDatabase(void)
	{
		return m_Impl->completelyDestroyDatabase();
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
		// load the data from files into unordered_map
		const std::filesystem::directory_iterator& iterator = std::filesystem::directory_iterator(getDirectory());
		
		for (std::filesystem::directory_entry file : iterator) {
			if (file.exists() && file.is_regular_file() && !file.is_directory()) { // if a file
				if (file.path().extension() == KV_STRING_EXTENSION) {	// if a kv file
					// open the file
					std::ifstream readableFile;
					readableFile.open(file.path().string());
					std::string key;
					key = file
						.path()
						.filename()
						.string()
						.substr(0, file.path().filename().string().length() - std::string(KV_STRING_EXTENSION).length());

					// read the file
					std::string value;
					readableFile.seekg(0, std::ios::end);
					value.reserve(readableFile.tellg());
					readableFile.seekg(0, std::ios::beg);
					value.assign((std::istreambuf_iterator<char>(readableFile)), std::istreambuf_iterator<char>());

					m_KeyValue_Store.insert({ key, value });

				}
			}
		}

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

		const auto& it = m_KeyValue_Store.find(key);

		if (it != m_KeyValue_Store.end()) {
			return it->second;
		}

		return defaultValue;

		/* OLD FIND CODE
		// check if file exists
		if (std::filesystem::exists(m_Directory / std::filesystem::path(key + KV_STRING_EXTENSION))) {

			// open the file
			std::ifstream file;
			file.open(m_Directory / std::filesystem::path(key + KV_STRING_EXTENSION));

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
		*/
	}

	void Database::DatabaseImpl::setValue(std::string key, std::string value)
	{
		// create a entry in the folder as .kv
		std::ofstream file;
		file.open(m_Directory / (key + KV_STRING_EXTENSION), std::ios::out | std::ios::trunc);
		file << value;
		file.close();

		// store on map
		m_KeyValue_Store.insert({ key, value });
	}

	void Database::DatabaseImpl::completelyDestroyDatabase(void)
	{
		if (std::filesystem::exists(m_Directory)) {
			std::filesystem::remove_all(m_Directory);
		}

		// clear the store m_KeyValue_Store
		m_KeyValue_Store.clear();
	}
}

