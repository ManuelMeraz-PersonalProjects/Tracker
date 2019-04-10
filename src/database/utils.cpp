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

auto database::utils::table_exists(std::string_view table_name) -> bool
{
  auto &sql_connection = Database::get_connection();
  std::stringstream sql_command;
  sql_command << "SELECT name FROM sqlite_master WHERE type='table' AND name='"
              << table_name << "'";

  std::string exists;
  try {
    sql_connection << sql_command.str(), soci::into(exists);
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to check if table exists "
                             "failed. Unexpected behavior.");
  }

  return exists != "";
}

auto database::utils::count_rows(std::string_view table_name) -> size_t
{
  if (!utils::table_exists(table_name)) { return 0; }

  auto &sql_connection = Database::get_connection();
  std::stringstream sql_command;
  sql_command << "SELECT count(*) from " << table_name;

  size_t num_rows;
  try {
    sql_connection << sql_command.str(), soci::into(num_rows);
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to count the number of rows in table "
                             "failed. Unexpected behavior.");
  }

  return num_rows;
}

void database::utils::create_table(std::string_view table_name,
                  std::vector<ColumnProperties> const &schema)
{
  std::stringstream sql_command;

  sql_command << "CREATE TABLE IF NOT EXISTS " << table_name << " (\n";

  auto delimeter = "";
  for (auto const &column : schema) {
    sql_command << delimeter << column.name << " "
                << utils::enum_to_string(column.data_type) << " "
                << utils::enum_to_string(column.constraint);

    delimeter = ",\n";
  }

  sql_command << ");\n";

  auto &sql_connection = Database::get_connection();

  try {
    sql_connection << sql_command.str();
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to create table failed!");
  }
}
