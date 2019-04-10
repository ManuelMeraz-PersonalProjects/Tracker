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
 * @brief Check if table exists in database
 *
 * @param table_name The name of the table
 *
 * Creates the following SQLite3 command:
 *
 * SELECT name FROM sqlite_master WHERE type='table' AND name='table_name';
 */
auto table_exists(std::string_view table_name) -> bool;

/**
 * @brief Count the number of rows in the table
 *
 * @param table_name The name of the table
 *
 * Creates the following SQLite3 command:
 *
 * SELECT name FROM sqlite_master WHERE type='table' AND name='table_name';
 */
auto count_rows(std::string_view table_name) -> size_t;

/**
 * @brief Create table if not exists
 *
 * @param table_name The name of the table to be created
 * @param schema The schema to be used to create the table
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
void create_table(std::string_view table_name,
                  std::vector<ColumnProperties> const &schema);

/**
 * @brief to_string function for data enum types
 *
 * @param DataEnum type that is either a constraint type or sql type
 */
template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int> = 0>
auto enum_to_string(DataEnum const &data_enum)
{
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
void insert(Storable const &storable)
{
  Data const &data = storable.get_data();
  if (!utils::table_exists(data.table_name)) {
    utils::create_table(data.table_name, data.schema);
  }

  std::stringstream sql_command;

  sql_command << "INSERT INTO " << data.table_name << "(\n";

  std::stringstream column_names;
  std::stringstream column_values;
  column_values << "VALUES\n(\n";

  // The row will be of length one because it comes from a single Storable
  // object
  auto delimeter = "";
  for (auto const &[column, row_data] :
       ranges::view::zip(data.schema, data.rows[0].row_data)) {

    // Contins a std::variant type, need to visit and extract the data
    auto row_index_type = static_cast<RowIndexType>(row_data.index());

    column_names << delimeter << column.name;
    column_values << delimeter;

    switch (row_index_type) {
    case RowIndexType::DOUBLE:
      column_values << std::get<double>(row_data);
      break;
    case RowIndexType::STRING:
      column_values << std::get<std::string>(row_data);
      break;
    case RowIndexType::INT:
      column_values << std::get<int>(row_data);
      break;
    case RowIndexType::LL:
      column_values << std::get<long long>(row_data);
      break;
    case RowIndexType::ULL:
      column_values << std::get<unsigned long long>(row_data);
      break;
    case RowIndexType::TIME:
      column_values << asctime(&std::get<std::tm>(row_data));
      break;
    default:
      throw std::runtime_error("Invalid variant type get!");
    };

    delimeter = ",\n";
  }

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
template <typename Storable,
          typename std::enable_if_t<
              std::is_base_of_v<database::Storable, Storable>, int> = 0>
auto retrieve() -> std::optional<std::vector<Storable>>
{
  constexpr auto type_string = nameof::nameof_type<Storable>();

  // namespace::Class -> Class
  // "Class" is the table name
  std::string table_name = type_string | ranges::view::reverse |
                           ranges::view::delimit(':') | ranges::view::reverse;

  auto &sql_connection = Database::get_connection();
  size_t num_rows = utils::count_rows(table_name);

  std::stringstream sql_command;
  sql_command << "SELECT * from " << table_name;

  soci::row from_row;
  soci::statement statement =
      (sql_connection.prepare << sql_command.str(), soci::into(from_row));
  try {
    statement.execute();
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;

    return std::nullopt;
  }

  // Getting data from soci row to tracker row
  Row to_row;
  to_row.row_data.reserve(from_row.size());

  // Schema contains the column names to map the data correctly
  std::vector<ColumnProperties> schema;
  schema.reserve(from_row.size());

  std::vector<Storable> storables;
  storables.reserve(num_rows);

  while (statement.fetch()) {
    for (size_t i = 0; i < from_row.size(); ++i) {

      const soci::column_properties &props = from_row.get_properties(i);
      ColumnProperties column_property;
      column_property.name = props.get_name();
      schema.emplace_back(column_property);

      switch (props.get_data_type()) {
      case soci::dt_string:
        to_row.row_data.emplace_back(from_row.get<std::string>(i));
        break;
      case soci::dt_double:
        to_row.row_data.emplace_back(from_row.get<double>(i));
        break;
      case soci::dt_integer:
        to_row.row_data.emplace_back(from_row.get<int>(i));
        break;
      case soci::dt_long_long:
        to_row.row_data.emplace_back(from_row.get<long long>(i));
        break;
      case soci::dt_unsigned_long_long:
        to_row.row_data.emplace_back(from_row.get<unsigned long long>(i));
        break;
      case soci::dt_date:
        to_row.row_data.emplace_back(from_row.get<std::tm>(i));
        break;
      }
    }

    // Construct default storable
    storables.emplace_back();
    storables.back().set_data(schema, to_row);
  }

  return std::optional<std::vector<Storable>>{storables};
}

} // namespace utils
} // namespace database

#endif /* DATABASE_UTILS_HPP */
