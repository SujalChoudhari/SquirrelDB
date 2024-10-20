#pragma once
#include <filesystem>
#include "IDatabase.h"



namespace SquirrelDB {
	class KeyValueStore : public IDatabase {

	public:
		KeyValueStore(const std::string& dbName, const std::string& fullPath);
		~KeyValueStore();

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