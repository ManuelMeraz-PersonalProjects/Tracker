/**
 * @file utils.h
 * @author Manuel G. Meraz
 * @date 03-28-2019
 * @brief Utility functions and objects for databasing
 */

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include "database/Data.hpp" // Data, ColumnInfo
#include "database/Database.hpp"
#include "database/Storable.hpp"
#include <algorithm>
#include <sstream>

namespace database {
/**
 * @brief Utility functions to insert, retrieve, and manipulate objects in
 *				database.
 */
namespace utils {

/**
 * @brief Create table if not exists
 *
 * @param table_name The name of the table to create
 *
 * Creates the following SQLite3 command to creare a table if it
 * does not exist:
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
// void create_table(const std::string table_name) {
// std::stringstream sql_command;
// Database::execute(sql_command.str());
//}

/**
 * @brief Gets data from any storable object and inserts it into relevant
 *				database
 *
 * @param storable The object containing data to be stored in a database
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
template <typename Storable> void insert(const Storable &storable) {
  const Data &data = storable.get_data();

  std::stringstream sql_command;

  sql_command << "INSERT INTO " << data.table_name << "(\n";

  std::stringstream column_values;
  column_values << "VALUES\n(\n";

  std::stringstream column_names;
  const auto append_values = [&column_names, &column_values](const auto &pair) {
    const std::string column_name = pair.first;
    const ColumnInfo column_info = pair.second;

    column_names << column_name << ",\n";
    column_values << column_info.value << ",\n";
  };

	// Up to second to last column
	std::for_each(begin(data.columns), prev(end(data.columns)), append_values);

  const auto last_column = prev(end(data.columns));

  const std::string last_column_name = last_column->first;
  const std::string last_value = last_column->second.value;
  column_names << last_column_name << ")\n";
  column_values << last_value << ")\n";

  sql_command << column_names.str() << column_values.str() << ";";
  Database::execute(sql_command.str());
}

// template <typename Storable, typename Property>
// auto retrieve(Type type, Property property) = delete;

} // namespace utils

} // namespace database

#endif /* DATABASE_UTILS_HPP */
