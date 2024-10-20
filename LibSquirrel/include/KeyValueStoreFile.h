#pragma once
#include <filesystem>
#include "IDatabase.h"



namespace SquirrelDB {
	class KeyValueStoreFile : public IDatabase {

	public:
		KeyValueStoreFile(const std::string& dbName, const std::string& fullPath);
		~KeyValueStoreFile();

		class KeyValueStoreFileImpl;
		std::filesystem::path			getDirectory(void)									const;
		std::string						getDatabaseName(void)								const;
		std::string						getValue(std::string key, std::string defaultValue) const;
		void							setValue(std::string key, std::string value);
		void							completelyDestroyDatabase(void);

	private:
		std::shared_ptr<KeyValueStoreFileImpl>	m_Impl;
	};
}