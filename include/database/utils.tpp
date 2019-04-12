/**
 * @file utils.tpp
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
#include <queue>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <class ForwardIt, class T, class Compare>
ForwardIt database::utils::binary_find(ForwardIt first, ForwardIt last,
                                       const T &value, Compare comp)
{
  // Use a less than comp to find:
  // auto const comp = [](Storable const& value, Storable const& found) {
  //    return value.id() < found.id();
  //}

  first = std::lower_bound(first, last, value, comp);
  return first != last && !comp(value, *first) ? first : last;
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline auto database::utils::count_rows() -> size_t
{
  if (!utils::table_exists<Storable>()) { return 0; }

  auto &sql_connection = Database::get_connection();
  std::string const table_name = utils::type_to_string<Storable>();

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

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline void
database::utils::create_table(std::vector<ColumnProperties> const &schema)
{
  std::string const table_name = utils::type_to_string<Storable>();

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

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
void database::utils::delete_storable(Storable const &storable)
{
  auto &storables = utils::retrieve_all<Storable>();

  auto const compare = [](Storable const &lhs, Storable const &rhs) {
    return lhs.id() < rhs.id();
  };

  auto &found =
      utils::binary_find(begin(storables), end(storables), storable, compare);

  if (found == end(storables)) {
    throw std::runtime_error("Impossible to delete an id that doesn't exist");
  }

  auto &sql_connection = Database::get_connection();
  std::string const table_name = utils::type_to_string<Storable>();

  // Found the id, swap with the back, remove from back, sort
  std::swap(*found, *prev(end(storables)));
  storables.pop_back();
  std::sort(begin(storables), end(storables),
            [](Storable const &lhs, Storable const &rhs) {
              return lhs.id() < rhs.id();
            });

  std::stringstream sql_command;
  sql_command << "DELETE FROM " << table_name << " WHERE " << table_name
              << "_id = " << storable.id();

  try {
    sql_connection << sql_command.str();
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to delete object failed!");
  }
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline void database::utils::drop_table()
{
  // Table doesn't exist, already 'dropped'
  if (!utils::table_exists<Storable>()) return;

  auto &sql_connection = Database::get_connection();
  std::string const table_name = utils::type_to_string<Storable>();

  std::stringstream sql_command;
  sql_command << "DROP TABLE " << table_name << "\n";

  try {
    sql_connection << sql_command.str();
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to drop table failed!");
  }
}

template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int>>
inline auto database::utils::enum_to_string(DataEnum const &data_enum)
    -> std::string_view
{
  if constexpr (std::is_same_v<DataEnum, DataType>) {
    static std::unordered_map<DataType, std::string_view> type_strings{
        {DataType::REAL, "REAL"},
        {DataType::INTEGER, "INTEGER"},
        {DataType::TEXT, "TEXT"},
        {DataType::NULL_, "NULL"},
        {DataType::BLOB, "BLOB"}};

    return type_strings[data_enum];
  } else { // Constraint Enum
    static std::unordered_map<Constraint, std::string_view> type_strings{
        {Constraint::PRIMARY_KEY, "PRIMARY KEY"},
        {Constraint::UNIQUE, "UNIQUE"},
        {Constraint::NOT_NULL, "NOT NULL"},
        {Constraint::CHECK, "CHECK"}};

    return type_strings[data_enum];
  }
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
auto database::utils::get_new_id() -> int
{
  auto &storables = utils::retrieve_all<Storable>();

  int new_id = 0;
  // Empty or first value is not 1
  if ((storables.size() >= 1 && storables[0].id() != 1) || storables.empty()) {
    new_id = 1;

    // First element is equal to one, can't use adjacent find
  } else if (storables.size() == 1 && storables[0].id() == 1) {
    new_id = 2;
  } else {
    // Find a gap in the sorted vector of IDs
    // if a gap exists, this is a deleted key.
    auto const is_deleted_key = [](Storable const &s, Storable const &s_next) {
      return (s.id() - s_next.id()) != 1;
    };

    auto potential_id =
        std::adjacent_find(begin(storables), end(storables), is_deleted_key);

    if (potential_id != end(storables)) {
      new_id = (*potential_id).id() + 1;
    } else {
      new_id = storables.size() + 1;
    }
  }

  storables.emplace_back(new_id);

  auto const compare = [](Storable const &lhs, Storable const &rhs) {
    return lhs.id() < rhs.id();
  };
  std::sort(begin(storables), end(storables), compare);

  return new_id;
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline void database::utils::insert(Storable const &storable)
{
  auto &storables = utils::retrieve_all<Storable>();
  auto const compare = [](Storable const &lhs, Storable const &rhs) {
    return lhs.id() < rhs.id();
  };

  if (!std::binary_search(begin(storables), end(storables), storable,
                          compare)) {
    throw std::runtime_error("Must never insert a deleted object back into the "
                             "database. Copy construct a new object");
  }

  // Data contains all of the table information
  // (e.g. table_name, schema and row(s) of data)
  Data const &data = storable.get_data();

  if (!utils::table_exists<Storable>()) {
    utils::create_table<Storable>(data.schema);
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
    column_names << delimeter << column.name;
    column_values << delimeter;

    utils::visit_row_data(
        [&column_values = column_values](auto const &row_data) {
          column_values << row_data;
        },
        row_data);

    delimeter = ",\n";
  }

  column_names << ")\n";
  column_values << ")\n";

  sql_command << column_names.str() << column_values.str();
  auto &sql_connection = Database::get_connection();

  try {
    sql_connection << sql_command.str();
  } catch (const soci::sqlite3_soci_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to insert storabled failed!");
  }
}

template <
    typename Storable, typename... Args,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
auto database::utils::make(Args &&... args) -> Storable &
{
  int const id = utils::get_new_id<Storable>();
  return Storable::make(id, std::forward<Args>(args)...);
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline auto database::utils::retrieve_all()
    -> std::vector<Storable, struct Storable::Allocator> &
{
  static bool data_is_loaded = false;
  static std::vector<Storable, struct Storable::Allocator> storables;

  if (!data_is_loaded) {
    std::string const table_name = utils::type_to_string<Storable>();

    auto &sql_connection = Database::get_connection();
    size_t num_rows = utils::count_rows<Storable>();

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
      throw std::runtime_error(
          " Failed to retrieve all storables from database");
    }

    // Schema contains the column names to map the data correctly
    std::vector<ColumnProperties> schema;
    schema.reserve(from_row.size());

    std::vector<Row> to_rows;
    to_rows.reserve(num_rows);

    while (statement.fetch()) {

      // Getting data from soci row to tracker row
      Row to_row;
      to_row.row_data.reserve(from_row.size());

      for (size_t i = 0; i < from_row.size(); ++i) {
        soci::column_properties const &props = from_row.get_properties(i);

        if (schema.size() < from_row.size()) {
          ColumnProperties column_property;
          column_property.name = props.get_name();
          schema.emplace_back(column_property);
        }

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

      to_rows.emplace_back(to_row);
    }

    // This is done after fetching the data from the rows
    // because while(statement.fetch()) goes into an infinite
    // loop if this is done inside the loop because we insert/update
    // storable data as they're constructed
    storables.reserve(num_rows);
    for (auto const &row : to_rows) {
      storables.emplace_back(schema, row);
    }

    data_is_loaded = true;
  }

  return storables;
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
auto database::utils::table_exists() -> bool
{
  auto &sql_connection = Database::get_connection();
  std::string const table_name = utils::type_to_string<Storable>();

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

template <typename T>
inline auto database::utils::type_to_string() -> std::string
{
  constexpr auto type_string = nameof::nameof_type<std::decay_t<T>>();

  // namespace::Class -> Class
  // "Class" is the table name
  std::string const table_name = type_string | ranges::view::reverse |
                                 ranges::view::delimit(':') |
                                 ranges::view::reverse;

  return table_name;
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
void database::utils::update(Storable const &storable)
{
  auto &storables = utils::retrieve_all<Storable>();
  auto const compare = [](Storable const &lhs, Storable const &rhs) {
    return lhs.id() < rhs.id();
  };

  // Not an already existing ID, can't update
  if (!std::binary_search(begin(storables), end(storables), storable,
                          compare)) {
    utils::insert(storable);
  }
  auto &sql_connection = Database::get_connection();

  // Data contains all of the table information
  // (e.g. table_name, schema and row(s) of data)
  Data const &data = storable.get_data();

  std::stringstream sql_command;
  sql_command << "UPDATE " << data.table_name << "\n";
  sql_command << "SET ";

  auto delimeter = "\n";
  // build this part of the SQL command: column_name = column_data,
  for (auto const &[column, row_data] :
       ranges::view::zip(data.schema, data.rows[0].row_data)) {
    // We need the food id to find the object
    // in the database.
    if (column.name == data.table_name + "_id") { continue; }

    sql_command << delimeter << column.name << " = ";

    utils::visit_row_data(
        [&sql_command = sql_command](auto const &row_data) {
          sql_command << row_data;
        },
        row_data);

    delimeter = ",\n";
  }

  sql_command << "\nWHERE " << data.table_name << "_id = " << storable.id();

  try {
    sql_connection << sql_command.str();
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to update food failed.");
  }
}

template <typename Lambda>
void database::utils::visit_row_data(Lambda const &handler,
                                     Row::row_data_t const &row_data)
{
  // Contins a std::variant type, need to visit and extract the data
  // index gives us the position in the template declaration, and therefore
  // the data type (e.g. <int, double> -> <0, 1>
  auto row_index_type = static_cast<soci::data_type>(row_data.index());

  switch (row_index_type) {
  case soci::dt_double:
    handler(std::get<double>(row_data));
    break;
  case soci::dt_string:
    handler(std::get<std::string>(row_data));
    break;
  case soci::dt_integer:
    handler(std::get<int>(row_data));
    break;
  case soci::dt_long_long:
    handler(std::get<long long>(row_data));
    break;
  case soci::dt_unsigned_long_long:
    handler(std::get<unsigned long long>(row_data));
    break;
  case soci::dt_date:
    char buffer[50];
    handler(asctime_r(&std::get<std::tm>(row_data), buffer));
    break;
  default:
    throw std::runtime_error("Invalid variant type get!");
  }
}
