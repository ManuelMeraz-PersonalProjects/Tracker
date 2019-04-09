/**
 * @file utils.hpp
 * @author Manuel G. Meraz
 * @date 03/30/2019
 * @brief Utility functions and objects for databasing
 */

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include "database/Data.hpp" // Data, ColumnInfo
#include "database/Database.hpp"
#include "database/Storable.hpp"
#include <iostream>   // cerr
#include <nameof.hpp> // NAMEOF
#include <optional>
#include <range/v3/all.hpp>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <vector>

/**
 * @brief Organizes all databasing related classes and functions 
 */
namespace database {
/**
 * @brief Utility functions to insert, retrieve, and manipulate objects in
 *        database.
 */
namespace utils {

/**
 * @brief to_string function for data enum types
 *
 * @param DataEnum type that is either a constraint type or sql type
 *
 */
template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int> = 0>
auto enum_to_string(const DataEnum &data_enum) {
  if constexpr (std::is_same_v<DataEnum, DataType>) {
    static std::map<DataType, std::string_view> type_strings{
        {DataType::REAL, "REAL"},
        {DataType::INTEGER, "INTEGER"},
        {DataType::TEXT, "TEXT"},
        {DataType::NULL_, "NULL"},
        {DataType::BLOB, "BLOB"}};

    return type_strings[data_enum];
  } else { // Constraint Enum
    static std::map<Constraint, std::string_view> type_strings{
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
 * @param data Data contains the table name and schema information
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

  auto delimeter = "";
  for (const Column &column : data.columns) {
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
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void insert(const Storable &storable) {
  const Data &data = storable.get_data();
  utils::create_table(data);

  std::stringstream sql_command;

  sql_command << "INSERT INTO " << data.table_name << "(\n";

  std::stringstream column_names;
  std::stringstream column_values;
  column_values << "VALUES\n(\n";

  auto delimeter = "";
  for (const Column &column : data.columns) {
    // Let the database generate a value for the primary key
    if (column.constraint == database::Constraint::PRIMARY_KEY) {
      continue;
    }

    column_names << delimeter << column.name;
    column_values << delimeter << column.value;
    delimeter = ",\n";
  };

  column_names << ")\n";
  column_values << ")\n";

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
 * Retrieves all objects of the type requested that contain that name. Does
 * not guarantee that the objects exist. This will either return an std
 * optional with nothing in it, a single object, or a vector.
 *
 * SELECT * from table;
 *
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<database::Storable, Storable>, int> = 0>
auto retrieve() -> std::optional<std::vector<std::string>> {
  constexpr auto type_string = nameof::nameof_type<Storable>();

  // namespace::Class -> Class
  // "Class" is the table name
  std::string table_name = type_string 
                          | ranges::view::reverse 
                          | ranges::view::delimit(':') 
                          | ranges::view::reverse;

  std::stringstream sql_command;
  sql_command << "SELECT count(*) from " << table_name;

  size_t table_size = 0;
  auto &sql_connection = Database::get_connection();

  try {
    sql_connection << sql_command.str(), soci::into(table_size);

  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;

    return std::nullopt;
  }

  // Reset stringstream
  sql_command.str("");
  sql_command.clear();

  sql_command << "SELECT name from " << table_name;
  std::vector<std::string> storables(table_size);
  try {
    sql_connection << sql_command.str(), soci::into(storables);

  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;

    return std::nullopt;
  }

  return storables;
}

} // namespace utils

} // namespace database

#endif /* DATABASE_UTILS_HPP */
