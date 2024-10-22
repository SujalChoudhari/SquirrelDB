#pragma once
#include <filesystem>
#include "IDatabase.h"



namespace SquirrelDB {

	template <typename K, typename V>
	class KeyValueStore : public IDatabase {

	public:
		KeyValueStore(const std::string& dbName, const std::string& fullPath);
		~KeyValueStore();

		class KeyValueStoreImpl;
		std::filesystem::path			getDirectory(void)									const;
		std::string						getDatabaseName(void)								const;
		V								getValue(K key, V defaultValue)						const;
		void							setValue(K key, V value);
		void							completelyDestroyDatabase(void);

	private:
		std::shared_ptr<KeyValueStoreImpl>	m_Impl;
	};
}