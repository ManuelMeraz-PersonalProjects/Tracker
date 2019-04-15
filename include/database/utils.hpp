/**
 * @file utils.hpp
 * @author Manuel G. Meraz
 * @date 03/30/2019
 * @brief Utility functions and objects for databasing
 */

#pragma once

#include "database/Data.hpp" // Data, Row, ColumnProperties
#include "database/Database.hpp"
#include "database/Storable.hpp"

#include <nameof.hpp>       // NAMEOF
#include <range/v3/all.hpp> //ranges

#include <iostream> // cerr
#include <sstream>
#include <string_view>
#include <type_traits>
#include <unordered_map>
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
 * @brief Finds and returns the object if it exists in the stl container
 * @param first A forward iterator for the start of the search
 * @param last A forward iterator for the end of the search
 * @param comp A less than comparison function for the object to be found
 * @return An iterator to the found object, will be the end iterator if now
 *         found
 *
 * Source: https://en.cppreference.com/w/cpp/algorithm/lower_bound
 *
 * Requirements: Container must be sorted in relation to the comparison
 *               function
 *
 * Usage:
 * @n auto const compare = [](Storable const &lhs, Storable const &rhs) {
 * @n  return lhs.id() < rhs.id();
 * @n };
 *
 * @n auto found = utils::binary_find(begin(storables), end(storables));
 * @n if(found != end(storables) {
 * @n   // Do something with found object
 * @n }
 */
template <class ForwardIt, class T, class Compare = std::less<>>
auto binary_find(ForwardIt first, ForwardIt last, const T &value, Compare comp)
    -> ForwardIt;

/**
 * @brief Count the number of Storable type in the database
 * @param Storable Any type that is a base of Storable
 * @return The number of rows in the table, 0 if table does not exist
 *
 * Creates the following SQLite3 command:
 * @n SELECT count(*) from table_name;
 *
 * Usage:
 * @n size_t quantity = database::utils::count_rows<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
auto count_rows() -> size_t;

/**
 * @brief Create table of Storable if not exists
 * @param Storable Any type that is a base of Storable
 * @param schema The schema to be used to create the table
 *
 * Creates the following SQLite3 command:
 * @n CREATE TABLE IF NOT EXISTS table_name (
 * @n  column_1 data_type PRIMARY KEY,
 * @n  column_2 data_type NOT NULL,
 * @n  column_3 data_type DEFAULT 0,
 * @n  ...
 * @n  );
 *
 * Usage:
 * @n database::utils::create_table<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
void create_table(std::vector<ColumnProperties> const &schema);

/**
 * @brief Delete Storable object from datbase and cache of storables
 * @param storable Any type that is a base of Storable
 *
 * Creates the following SQLite3 command:
 * @n DELETE
 * @n FROM
 * @n  table
 * @n WHERE
 * @n  search_condition;
 *
 * Usage:
 * @n database::utils::delete_storable(food);
 *
 * Note: delete is a keyword, could not use that.
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
void delete_storable(Storable const &storable);

/**
 * @brief Deletes the Storable table from the database
 * @param Storable Any type that is a base of Storable
 *
 * Creates the following SQLite3 command:
 * DROP TABLE table_name;
 *
 * Usage:
 * @n drop_table<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
void drop_table();

/**
 * @brief to_string function for data enum types
 * @param data_enum DataEnum type that is either a constraint type or sql type
 * @return a string view of the string version of the enum appropriate for a
 *         database
 *
 * Does not convert to exam string value, it converts to the the string
 * that will be used by the database.
 *
 * e.g. NULL_ -> "NULL", PRIMARY_KEY -> "PRIMARY KEY"
 */
template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int> = 0>
auto enum_to_string(DataEnum const &data_enum) -> std::string_view;

/**
 * @brief Generates new unique ID for the type being asked for
 * @param Storable Any type that is a base of Storable
 * @return A new id that is not being used by the database for this Storable
 *         type
 *
 * Usage:
 * @n int new_id = database::utils::get_new_id<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
auto get_new_id() -> int;

/**
 * @brief Gets data from any storable object and inserts it into relevant
 *        database
 *
 * @param storable The object containing data to be stored in a database. Must
 *                 inherit from Storable.
 *
 * Creates the following SQLite3 command:
 * @n INSERT INTO table1 (
 * @n column1,
 * @n column2 ,..)
 * @n VALUES
 * @n (
 * @n value1,
 * @n value2 ,...);
 *
 * Usage:
 * @n food::Food taco("taco", macros);
 * @n database::utils::insert(taco);
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
void insert(Storable const &storable);

/**
 * @brief Generates a new Storable object stores it in the cache, inserts it
 *        into the database, and returns a reference to tht new object.
 *
 * @param The arguments to construct the storable object.
 * @return A reference to the new object, copies are not allowed.
 *
 * Usage:
 * @n auto &some_food = database::utils::make<food::Food>("taco", macros);
 */
template <
    typename Storable, typename... Args,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
auto make(Args &&... args) -> Storable &;

/**
 * @brief Retrieves all database objects that match the Storable that is passed
 * in
 * @param Storable The type of storable object being retrieved
 * @return A reference to the vector containing all the storable objects of tht
 *         type
 *
 * Retrieves all objects of the type requested that contain that name.
 *
 * Creates the following SQLite3 command:
 * @n SELECT * from Storable;
 *
 * Note: Copies of storable objects not allowed
 *
 * Usage:
 * @n auto all_food = database::utils::retrieve_all<food::Food>();
 * @n for(auto const &food: all_food) {
 * @n   // do something
 * @n }
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
auto retrieve_all() -> std::vector<Storable, struct Storable::Allocator> &;

/**
 * @brief Check if Storable table exists in database
 * @param Storable Any type that is a base of Storable
 * @return true if the table exists, false otherwise
 *
 * Creates the following SQLite3 command:
 * @n SELECT name FROM sqlite_master WHERE type='table' AND name='table_name';
 *
 * Usage:
 * @n if(table_exists<food::Food>()) {
 * @n   // do something
 * @n }
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
auto table_exists() -> bool;

/**
 * @brief Converts a type to a string and trims the namespaces off.
 *                 (e.g. namespace::other_namespace::ClassName -> "ClassName")
 *
 * @param T The template parameter T could be any possible type.
 * @return A std::string of that type passed in as a template parameter
 *
 * Usage:
 * @n std::string type_string = database::utils::type_to_string<food::Food>();
 * @n type_string == "Food" // true
 */
template <typename T> auto type_to_string() -> std::string;

/**
 * @brief Updates the Storable objects data within the database
 * @param storable A storable object that already exists within the database
 *                 and will update the data
 *
 * Creates the following SQLite3 command:
 * @n UPDATE Storable
 * @n SET column_1 = new_value_1,
 * @n     colimn_2 = new_value_2,
 * @n     ...
 * @n WHERE Storable_id = Storable_id_value;
 *
 * Usage:
 * @n auto all_food = database::utils::retrieve_all<food::Food>();
 * @n if(all_food && all_food.size() > 0) {
 * @n   auto my_food = all_food.back();
 * @n   food.set_protein(100);
 * @n   database::utils::update(my_food);
 * @n  }
 *
 * Will throw a runtime error if food is not in the database!
 */
template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int> = 0>
void update(Storable const &storable);

/**
 * @brief Updates the Storable objects data within the database
 * @param handler A handler that will handle for the row_data_t once
 *                it passes the data into it.
 *
 * @param row_data A std::variant containing multiple data types. See
 *                 Row implementation or the implementation of this
 *                 function for all the types it contains.
 *
 * Usage:
 * @n std::stringstream column_values;
 * @n utils::visit_row_data(
 * @n     [&column_values = column_values](auto const &row_data) {
 * @n       column_values << row_data;
 * @n     },
 * @n     row_data);
 *
 * In this example we're using a capture initializer to prevent a dangling
 * reference.
 */
template <typename Lambda>
void visit_row_data(Lambda const &handler, Row::row_data_t const &row_data);

} // namespace utils
} // namespace database

///////////////////////////// Implementation Below /////////////////////////////

namespace {
/*
 * @brief flag used to determine if data has been loaded into cache or not
 */
template <typename Storable> static bool data_is_loaded = false;

template <typename Storable> static bool table_exists_flag = false;
} // namespace

template <class ForwardIt, class T, class Compare>
auto database::utils::binary_find(ForwardIt first, ForwardIt last,
                                  const T &value, Compare comp) -> ForwardIt
{
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
  auto const table_name = utils::type_to_string<Storable>();

  std::stringstream sql_command;
  sql_command << "SELECT count(*) from " << table_name << ";\n";

  size_t num_rows = 0;
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
  auto const table_name = utils::type_to_string<Storable>();

  std::stringstream sql_command;
  sql_command << "CREATE TABLE IF NOT EXISTS " << table_name << " (\n";

  auto delimeter = "";
  for (auto const &[name, data_type, constraint] : schema) {
    sql_command << delimeter << name << " " << utils::enum_to_string(data_type)
                << " " << utils::enum_to_string(constraint);

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

  table_exists_flag<Storable> = true;
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

  // Make sure the storable object exists before attempting to delete
  auto found =
      utils::binary_find(begin(storables), end(storables), storable, compare);

  if (found == end(storables)) {
    throw std::runtime_error("Impossible to delete an id that doesn't exist");
  }

  auto &sql_connection = Database::get_connection();
  auto const table_name = utils::type_to_string<Storable>();

  // Need to delete from database first, otherwise if we delete from
  // the vector of storables first, the references to the storable we're
  // referring to changes to a different ID.
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

  storables.erase(found);
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline void database::utils::drop_table()
{
  // Table doesn't exist, already 'dropped'
  if (!utils::table_exists<Storable>()) { return; }

  auto &sql_connection = Database::get_connection();
  auto const table_name = utils::type_to_string<Storable>();

  std::stringstream sql_command;
  sql_command << "DROP TABLE " << table_name << "\n";

  try {
    sql_connection << sql_command.str();
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to drop table failed!");
  }

  table_exists_flag<Storable> = false;
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
    // storables is sorted
    auto const is_deleted_key = [](Storable const &s, Storable const &s_next) {
      return (s_next.id() - s.id()) > 1;
    };

    auto potential_id =
        std::adjacent_find(begin(storables), end(storables), is_deleted_key);

    if (potential_id != end(storables)) {
      new_id = (*potential_id).id() + 1;
    } else {
      new_id = storables.size() + 1;
    }
  }

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
    data_is_loaded<Storable> = true;
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

    // Prevent dangling reference with capture init
    auto const visitor = [&col_vals = column_values](auto const &row_data) {
      col_vals << row_data;
    };

    utils::visit_row_data(visitor, row_data);

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
  auto &storables = database::utils::retrieve_all<Storable>();

  auto const comp = [](Storable const &lhs, int id) { return lhs.id() < id; };

  // Find the position to insert in the cache
  auto pos = std::lower_bound(begin(storables), end(storables), id, comp);

  // Store into local cache
  auto &storable = *storables.emplace(pos, id, std::forward<Args>(args)...);

  // Insert into the database
  database::utils::insert(storable);

  return storable;
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
inline auto database::utils::retrieve_all()
    -> std::vector<Storable, struct Storable::Allocator> &
{
  static std::vector<Storable, struct Storable::Allocator> storables;

  if (!data_is_loaded<Storable>) {
    data_is_loaded<Storable> = true;
    auto const table_name = utils::type_to_string<Storable>();

    auto &sql_connection = Database::get_connection();
    size_t num_rows = utils::count_rows<Storable>();
    if (num_rows == 0) return storables;

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
  }

  return storables;
}

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
auto database::utils::table_exists() -> bool
{
  if (!table_exists_flag<Storable>) {
    auto &sql_connection = Database::get_connection();
    auto const table_name = utils::type_to_string<Storable>();

    std::stringstream sql_command;
    sql_command
        << "SELECT name FROM sqlite_master WHERE type='table' AND name='"
        << table_name << "';\n";

    std::string exists;
    try {
      sql_connection << sql_command.str(), soci::into(exists);
    } catch (soci::sqlite3_soci_error const &error) {
      std::cerr << error.what() << std::endl;
      std::cerr << sql_command.str() << std::endl;
      throw std::runtime_error("Attempt to check if table exists failed.");
    }

    table_exists_flag<Storable> = !exists.empty();
  }

  return table_exists_flag<Storable>;
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
