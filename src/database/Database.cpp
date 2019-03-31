/**
 * @file Database.cpp
 * @author Manuel G. Meraz
 * @date 03/30/2019
 * @brief The database singleton class is in charge all database queries
 *
 *  Due to the way SQLite works, we want a single connection to the database
 *  up and running at all times. This class keeps the connection maintained.
 */

#include "database/Database.hpp"
#include <iostream>
#include <string>

static std::unique_ptr<soci::session> _instance = nullptr;

//! @copydoc Database::execute(std::string)
void Database::execute(const std::string &sql_command) {
  if (!_instance) {
    _instance = std::make_unique<soci::session>(
        "sqlite3", "db=tracker.db timeout=2 shared_cache=true");
  }
  try {
    *_instance << sql_command;
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command << std::endl;
  }
}
