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
	template<typename K, typename V>
	class KeyValueStore<K, V>::KeyValueStoreImpl : public IDatabase
	{

	public:
		KeyValueStoreImpl(const std::string& dbName, const std::string& fullPath);
		std::filesystem::path getDirectory(void) const;
		std::string getDatabaseName(void) const;
		V getValue(K key, V defaultValue) const;
		void setValue(K key, V value);
		void completelyDestroyDatabase(void);

	private:
		std::string m_DatabaseName;
		std::filesystem::path m_Directory;
		std::unordered_map<K, V> m_KeyValue_Store;
	};
}



/// <summary>
/// Database Implementations
/// </summary>
namespace SquirrelDB
{
	template <typename K, typename V>
	KeyValueStore<K, V>::KeyValueStore(const std::string& dbName, const std::string& fullPath)
	{
		m_Impl = std::make_unique<KeyValueStoreImpl>(dbName, fullPath);
	}

	template <typename K, typename V>
	KeyValueStore<K, V>::~KeyValueStore()
	{
		// unique_ptr will automatically delete m_Impl when Database is destroyed.
		// No need to manually do anything here.
	}

	template <typename K, typename V>
	std::filesystem::path KeyValueStore<K, V>::getDirectory(void) const
	{
		return m_Impl->getDirectory();
	}

	template <typename K, typename V>
	std::string KeyValueStore<K, V>::getDatabaseName(void) const
	{
		return m_Impl->getDatabaseName();
	}

	template <typename K, typename V>
	V KeyValueStore<K, V>::getValue(K key, V defaultValue) const
	{
		return m_Impl->getValue(key, defaultValue);
	}

	template <typename K, typename V>
	void KeyValueStore<K, V>::setValue(K key, V value)
	{
		return m_Impl->setValue(key, value);

	}

	template <typename K, typename V>
	void KeyValueStore<K, V>::completelyDestroyDatabase(void)
	{
		return m_Impl->completelyDestroyDatabase();
	}
}


/// <summary>
/// DatabaseImpl Implementation
/// </summary>
namespace SquirrelDB
{

	template <typename K, typename V>
	KeyValueStore<K, V>::KeyValueStoreImpl::KeyValueStoreImpl(const std::string& dbName, const std::string& fullPath)
		: m_DatabaseName(dbName), m_Directory(std::filesystem::path(fullPath))
	{
		// Load the data from files into unordered_map
		const std::filesystem::directory_iterator& iterator = std::filesystem::directory_iterator(getDirectory());

		for (const std::filesystem::directory_entry& file : iterator) {
			if (file.exists() && file.is_regular_file() && !file.is_directory()) {
				if (file.path().extension() == KV_STRING_EXTENSION) {
					// Open the file
					std::ifstream readableFile;
					readableFile.open(file.path().string());
					std::string key = file.path().filename().string().substr(0, file.path().filename().string().length() - std::string(KV_STRING_EXTENSION).length());

					// Read the file
					V value;
					readableFile.seekg(0, std::ios::end);
					std::string buffer;
					buffer.reserve(readableFile.tellg());
					readableFile.seekg(0, std::ios::beg);
					buffer.assign((std::istreambuf_iterator<char>(readableFile)), std::istreambuf_iterator<char>());
					std::istringstream stream(buffer);
					stream >> value;

					// Store the key-value pair
					m_KeyValue_Store.insert({ key, value });
				}
			}
		}
	}
	
	template <typename K, typename V>
	std::filesystem::path KeyValueStore<K, V>::KeyValueStoreImpl::getDirectory(void) const
	{
		return m_Directory;
	}

	template <typename K, typename V>
	std::string KeyValueStore<K, V>::KeyValueStoreImpl::getDatabaseName(void) const
	{
		return m_DatabaseName;
	}

	template <typename K, typename V>
	V KeyValueStore<K, V>::KeyValueStoreImpl::getValue(K key, V defaultValue) const
	{
		const auto& it = m_KeyValue_Store.find(key);
		if (it != m_KeyValue_Store.end()) {
			return it->second;
		}
		return defaultValue;
	}

	template <typename K, typename V>
	void KeyValueStore<K, V>::KeyValueStoreImpl::setValue(K key, V value)
	{
		// Create an entry in the folder as .kv
		std::ofstream file;
		file.open(m_Directory / (key + KV_STRING_EXTENSION), std::ios::out | std::ios::trunc);
		file << value;
		file.close();

		// Store in map
		m_KeyValue_Store[key] = value;
	}

	template <typename K, typename V>
	void KeyValueStore<K, V>::KeyValueStoreImpl::completelyDestroyDatabase(void)
	{
		if (std::filesystem::exists(m_Directory)) {
			std::filesystem::remove_all(m_Directory);
		}
		m_KeyValue_Store.clear();
	}

	// Explicit specialization for string keys and values
	template class KeyValueStore<std::string, std::string>;
}

