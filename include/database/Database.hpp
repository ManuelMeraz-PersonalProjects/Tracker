/**
 * @file Database.hpp
 * @author Manuel G. Meraz
 * @date 03/13/2019
 * @brief The database singleton class is in charge all database queries
 *
 *  Due to the way SQLite works, we want a single connection to the database
 *  up and running at all times. This class keeps the connection maintained.
 */

#ifndef DATABASE_DATABASE_HPP
#define DATABASE_DATABASE_HPP

#include "soci-sqlite3.h"
#include "soci.h"
#include <memory>
#include <string>

/**
 * @brief The database singleton class is in charge all database queries
 *
 *  Due to the way SQLite works, we want a single connection to the database
 *  up and running at all times. This class keeps the connection maintained.
 */
class Database {
public:
  /**
   * @brief Executes the passed in sqlite command
   *
   * Called by Database::utils
   */
  static void execute(const std::string& sql_command);

  //! Deleted functions
  Database(const Database &) = delete;
  Database(Database &&) = delete;
  Database &operator=(const Database &) = delete;
  Database &operator=(Database &&) = delete;

private:
  Database() = default;
  ~Database() = default;
  static std::unique_ptr<const soci::session> _sql;
};

#endif /* DATABASE_DATABASE_HPP */
