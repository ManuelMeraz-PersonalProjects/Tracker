/**
 * @file utils.cpp
 * @author Manuel G. Meraz
 * @date 04/09/2019
 * @brief Utility functions and objects for databasing
 */

#include "database/Database.hpp"
#include "database/utils.hpp"

#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

void database::utils::drop_table(std::string_view table_name)
{

  // Table doesn't exist, already 'dropped'
  if (!utils::table_exists(table_name)) return;

  auto &sql_connection = Database::get_connection();
  std::stringstream sql_command;
  sql_command << "DROP TABLE " << table_name << ";\n";

  try {
    sql_connection << sql_command.str();
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to drop table failed!");
  }
}

auto database::utils::table_exists(std::string_view table_name) -> bool
{
  auto &sql_connection = Database::get_connection();
  std::stringstream sql_command;
  sql_command << "SELECT name FROM sqlite_master WHERE type='table' AND name='"
              << table_name << "';\n";

  std::string exists;
  try {
    sql_connection << sql_command.str(), soci::into(exists);
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to check if table exists failed.");
  }

  return exists != "";
}
