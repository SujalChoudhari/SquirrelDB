#include "pch.h"
#include "include/IDatabase.h"
#include "include/KeyValueStore.h"
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
	class KeyValueStore::KeyValueStoreImpl : public IDatabase
	{

	public:
		KeyValueStoreImpl(const std::string& dbName, const std::string& fullPath);
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

	KeyValueStore::KeyValueStore(const std::string& dbName, const std::string& fullPath)
	{
		m_Impl = std::make_unique<KeyValueStoreImpl>(dbName, fullPath);
	}

	KeyValueStore::~KeyValueStore()
	{
		// unique_ptr will automatically delete m_Impl when Database is destroyed.
		// No need to manually do anything here.
	}


	std::filesystem::path KeyValueStore::getDirectory(void) const
	{
		return m_Impl->getDirectory();
	}

	std::string KeyValueStore::getDatabaseName(void) const
	{
		return m_Impl->getDatabaseName();
	}

	std::string KeyValueStore::getValue(std::string key, std::string defaultValue) const
	{
		return m_Impl->getValue(key, defaultValue);
	}

	void KeyValueStore::setValue(std::string key, std::string value)
	{
		return m_Impl->setValue(key, value);

	}

	void KeyValueStore::completelyDestroyDatabase(void)
	{
		return m_Impl->completelyDestroyDatabase();
	}
}


/// <summary>
/// DatabaseImpl Implementation
/// </summary>
namespace SquirrelDB
{

	KeyValueStore::KeyValueStoreImpl::KeyValueStoreImpl(const std::string& dbName, const std::string& fullPath)
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

	std::filesystem::path KeyValueStore::KeyValueStoreImpl::getDirectory(void) const
	{
		return m_Directory;
	}

	std::string KeyValueStore::KeyValueStoreImpl::getDatabaseName(void) const
	{
		return m_DatabaseName;
	}

	std::string KeyValueStore::KeyValueStoreImpl::getValue(std::string key, std::string defaultValue) const
	{

		const auto& it = m_KeyValue_Store.find(key);

		if (it != m_KeyValue_Store.end()) {
			return it->second;
		}

		return defaultValue;
	}

	void KeyValueStore::KeyValueStoreImpl::setValue(std::string key, std::string value)
	{
		// create a entry in the folder as .kv
		std::ofstream file;
		file.open(m_Directory / (key + KV_STRING_EXTENSION), std::ios::out | std::ios::trunc);
		file << value;
		file.close();

		// store on map
		m_KeyValue_Store.insert({ key, value });
	}

	void KeyValueStore::KeyValueStoreImpl::completelyDestroyDatabase(void)
	{
		if (std::filesystem::exists(m_Directory)) {
			std::filesystem::remove_all(m_Directory);
		}

		// clear the store m_KeyValue_Store
		m_KeyValue_Store.clear();
	}
}

