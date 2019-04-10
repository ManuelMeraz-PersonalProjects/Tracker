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

auto database::utils::count_rows(std::string_view table_name) -> size_t
{
  if (!utils::table_exists(table_name)) { return 0; }

  auto &sql_connection = Database::get_connection();
  std::stringstream sql_command;
  sql_command << "SELECT count(*) from " << table_name << ";\n";

  size_t num_rows;
  try {
    sql_connection << sql_command.str(), soci::into(num_rows);
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error(
        "Attempt to count the number of rows in table failed.");
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
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to create table failed!");
  }
}

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
