/**
 * @file utils.h
 * @author Manuel G. Meraz
 * @date 03-30-2019
 * @brief Utility functions and objects for databasing
 */

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include "database/Data.hpp" // Data, ColumnInfo
#include "database/Database.hpp"
#include "database/Storable.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <type_traits>

namespace database {
/**
 * @brief Utility functions to insert, retrieve, and manipulate objects in
 *        database.
 */
namespace utils {

/**
 * @brief to string function for data enum types
 *
 * @param DataEnum type that is either a constraint type or sql type
 *
 */
template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int> = 0>
const std::string to_string(const DataEnum &data_enum) {
  if constexpr (std::is_same_v<DataEnum, DataType>) {
    static std::map<DataType, std::string> type_strings{
        {DataType::REAL, "REAL"},
        {DataType::INTEGER, "INTEGER"},
        {DataType::TEXT, "TEXT"},
        {DataType::NULL_, "NULL"},
        {DataType::BLOB, "BLOB"}};

    return type_strings[data_enum];
  } else { // Constraint Enum
    static std::map<Constraint, std::string> type_strings{
        {Constraint::PRIMARY_KEY, "PRIMARY KEY"},
        {Constraint::UNIQUE, "UNIQUE"},
        {Constraint::NOT_NULL, "NOT NULL"},
        {Constraint::CHECK, "CHECK"}};

    return type_strings[data_enum];
  }
}

/**
 * @brief Create table if not exists
 *
 * @param table_name The name of the table to create
 *
 * Creates the following SQLite3 command to creare a table if it
 * does not exist:
 *
 *  CREATE TABLE IF NOT EXISTS table_name (
 *   column_1 data_type PRIMARY KEY,
 *   column_2 data_type NOT NULL,
 *   column_3 data_type DEFAULT 0,
 *   ...
 *   );
 *
 */
void create_table(const Data &data) {
  std::stringstream sql_command;

  sql_command << "CREATE TABLE IF NOT EXISTS " << data.table_name << " (\n";

  const auto build_column_string = [&sql_command](const Column &column) {
    sql_command << column.name << " " << utils::to_string(column.data_type)
                << " " << utils::to_string(column.constraint) << ",\n";
  };

  std::for_each(cbegin(data.columns), prev(cend(data.columns)),
                build_column_string);

  const auto &last_column = *prev(end(data.columns));

  // Add last column in without a comma at the end
  sql_command << last_column.name << " "
              << utils::to_string(last_column.data_type) << " "
              << utils::to_string(last_column.constraint) << "\n";

  sql_command << ");\n";

  auto &sql_connection = Database::get_connection();

  try {
    sql_connection << sql_command.str();
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
  }
}

/**
 * @brief Gets data from any storable object and inserts it into relevant
 *        database
 *
 * @param storable The object containing data to be stored in a database. Must
 *                 inherit from Storable.
 *
 * This function pulls data to be stored into a database and builds an SQL
 * command from the data like so:
 *
 * INSERT INTO table1 (
 * column1,
 * column2 ,..)
 * VALUES
 * (
 * value1,
 * value2 ,...);
 *
 */
template <typename Storable,
          typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void insert(const Storable &storable) {
  const Data &data = storable.get_data();
  utils::create_table(data);

  std::stringstream sql_command;

  sql_command << "INSERT INTO " << data.table_name << "(\n";

  std::stringstream column_values;
  column_values << "VALUES\n(\n";

  std::stringstream column_names;
  const auto append_values = [&column_names,
                              &column_values](const Column &column) {
    // Let the database generate a value for the primary key
    if (column.constraint == database::Constraint::PRIMARY_KEY) {
      return;
    }

    column_names << column.name << ",\n";
    column_values << column.value << ",\n";
  };

  // Up to second to last column
  std::for_each(cbegin(data.columns), prev(cend(data.columns)), append_values);

  // Add last column in without a comma at the end
  const auto &last_column = *prev(end(data.columns));

  column_names << last_column.name << ")\n";
  column_values << last_column.value << ")\n";

  sql_command << column_names.str() << column_values.str() << ";";
  auto &sql_connection = Database::get_connection();

  try {
    sql_connection << sql_command.str();
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
  }
}

/**
 * @brief Retrieves all database objects that match the name that is passed in
 *
 * @param name The name of the object being retrieved fro the database
 *
 * Retrieves all objects of the type requested that contain that name. Does not
 * guarantee that the objects exist. This will either return an std optional
 * with nothing in it, a single object, or a vector.
 *
 * SELECT * from table;
 *
 */
template <typename Storable,
          typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
Storable retrieve(const std::string &name) {
  std::stringstream sql_command;
  sql_command << "SELECT * from food";

  auto &sql_connection = Database::get_connection();

  Storable food;
  try {
    sql_connection << sql_command.str(), soci::into(food);
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
  }
  sql_command << name;

  return food;
}

} // namespace utils

} // namespace database

#endif /* DATABASE_UTILS_HPP */
