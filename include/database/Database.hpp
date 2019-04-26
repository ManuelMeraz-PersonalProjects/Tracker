/**
 * @file Database.hpp
 * @author Manuel G. Meraz
 * @date 03/13/2019
 * @brief Due to the way SQLite works, we want a single connection to the
 *        database up and running at all times. This class keeps the connection
 *        maintained.
 */

#pragma once

#include <soci-sqlite3.h>
#include <soci.h>

#include <memory>

// Necessary to load a database with statically linked soci library
extern "C" void soci::register_factory_sqlite3();

/**
 * @brief Organizes all databasing related classes and functions
 */
namespace database {
/**
 * @brief The database singleton class is in charge all database queries
 *
 *  Due to the way SQLite works, we want a single connection to the database
 *  up and running at all times. This class keeps the connection maintained.
 */
class Database {
public:
  /**
   * @brief Returns a reference to the current database connection;
   *
   * Need to return a reference explicitly because this item is uncopyable.
   * Attempts to copy the connection will try to call a private constructor and
   * fail.
   *
   * Usage:
   * @n auto& sql_connection = database::Database::get_connection();
   * @n sql_connection << "some sql command here";
   *
   * Will throw a soci::sqlite3_soci_error if the command fails
   */
  static auto get_connection() -> soci::session &;

  //! Deleted functions
  Database(const Database &) = delete;
  Database(Database &&) = delete;
  Database &operator=(const Database &) = delete;
  Database &operator=(Database &&) = delete;

private:
  Database() = default;
  ~Database() = default;

  static std::unique_ptr<soci::session> sql_connection;
};
} // namespace database
