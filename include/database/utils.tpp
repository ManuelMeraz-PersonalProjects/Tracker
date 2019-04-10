/**
 * @file utils.hpp
 * @author Manuel G. Meraz
 * @date 04/30/2019
 * @brief Utility functions and objects for databasing.
 *        Implements database/utils.hpp.
 */

#pragma once

#include "database/Data.hpp" // Data, ColumnInfo
#include "database/Database.hpp"
#include "database/Storable.hpp"
#include "database/utils.hpp"

#include <nameof.hpp> // NAMEOF
#include <range/v3/all.hpp>

#include <iostream> // cerr
#include <optional>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <vector>

template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int>>
inline auto database::utils::enum_to_string(DataEnum const &data_enum)
    -> std::string_view
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

template <typename Storable,
          typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int>>
inline void database::utils::insert(Storable const &storable)
{
  // Data contains all of the table information
  // (e.g. table_name, schema and row(s) of data)
  Data const &data = storable.get_data();
  if (!utils::table_exists(data.table_name)) {
    utils::create_table(data.table_name, data.schema);
  }

  std::stringstream sql_command;

  sql_command << "INSERT INTO " << data.table_name << "(\n";

  std::stringstream column_names;
  std::stringstream column_values;
  column_values << "VALUES\n(\n";

  // The row will be of length one because it
  // comes from a single Storable object
  auto delimeter = "";
  for (auto const &[column, row_data] :
       ranges::view::zip(data.schema, data.rows[0].row_data)) {
    // Contins a std::variant type, need to visit and extract the data
    // index gives us the position in the template declaration, and therefore
    // the data type (e.g. <int, double> -> <0, 1>
    auto row_index_type = static_cast<soci::data_type>(row_data.index());

    column_names << delimeter << column.name;
    column_values << delimeter;

    switch (row_index_type) {
    case soci::dt_double:
      column_values << std::get<double>(row_data);
      break;
    case soci::dt_string:
      column_values << std::get<std::string>(row_data);
      break;
    case soci::dt_integer:
      column_values << std::get<int>(row_data);
      break;
    case soci::dt_long_long:
      column_values << std::get<long long>(row_data);
      break;
    case soci::dt_unsigned_long_long:
      column_values << std::get<unsigned long long>(row_data);
      break;
    case soci::dt_date:
      char buffer[50];
      column_values << asctime_r(&std::get<std::tm>(row_data), buffer);
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

template <typename Storable,
          typename std::enable_if_t<
              std::is_base_of_v<database::Storable, Storable>, int>>
inline auto database::utils::retrieve() -> std::optional<std::vector<Storable>>
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
  } catch (soci::sqlite3_soci_error const &error) {
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
      soci::column_properties const &props = from_row.get_properties(i);
      ColumnProperties column_property;
      column_property.name = props.get_name();
      schema.emplace_back(column_property);

      switch (props.get_data_type()) {
      case soci::dt_double:
        to_row.row_data.emplace_back(from_row.get<double>(i));
        break;
      case soci::dt_string:
        to_row.row_data.emplace_back(from_row.get<std::string>(i));
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
      default:
        throw std::runtime_error("Invalid variant type get!");
      }
    }

    // Construct default storable
    storables.emplace_back();
    storables.back().set_data(schema, to_row);
  }

  return std::optional<std::vector<Storable>>{storables};
}
