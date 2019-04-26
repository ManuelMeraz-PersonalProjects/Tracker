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

std::unique_ptr<soci::session> database::Database::sql_connection = nullptr;

auto database::Database::get_connection() -> soci::session &
{
  if (!sql_connection) {
    soci::register_factory_sqlite3();
    sql_connection = std::make_unique<soci::session>(
        "sqlite3", "db=tracker.db timeout=2 shared_cache=true");
  }

  return *sql_connection;
}
