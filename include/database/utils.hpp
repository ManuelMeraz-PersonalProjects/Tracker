/**
 * @file utils.hpp
 * @author Manuel G. Meraz
 * @date 03/30/2019
 * @brief Utility functions and objects for databasing
 */

#pragma once

#include "database/Storable.hpp"

#include <optional>
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
 * @brief Converts a type to a string and trims the namespaces off.
 *                 (e.g. namespace::other_namespace::ClassName -> "ClassName")
 *
 * Usage:
 *
 * auto type_string = database::utils::type_to_string<food::Food>();
 *
 * type_string == "Food" // true
 *
 */
template <typename T> auto type_to_string() -> std::string;

/**
 * @brief Count the number of rows in the table
 * @param table_name The name of the table
 *
 * Creates the following SQLite3 command:
 *
 * SELECT count(*) from table_name;
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
auto count_rows() -> size_t;

/**
 * @brief Create table if not exists
 * @param table_name The name of the table to be created
 * @param schema The schema to be used to create the table
 *
 * Creates the following SQLite3 command:
 *
 *  CREATE TABLE IF NOT EXISTS table_name (
 *   column_1 data_type PRIMARY KEY,
 *   column_2 data_type NOT NULL,
 *   column_3 data_type DEFAULT 0,
 *   ...
 *   );
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void create_table(std::vector<ColumnProperties> const &schema);

/**
 * @brief Deletes the table from the database
 * @param table_name The name of the table to be created
 *
 * Creates the following SQLite3 command:
 *
 * DROP TABLE table_name;
 *
 */
void drop_table(std::string_view table_name);

/**
 * @brief Check if table exists in database
 * @param table_name The name of the table
 *
 * Creates the following SQLite3 command:
 *
 * SELECT name FROM sqlite_master WHERE type='table' AND name='table_name';
 */
auto table_exists(std::string_view table_name) -> bool;

/**
 * @brief to_string function for data enum types
 * @param data_enum DataEnum type that is either a constraint type or sql type
 */
template <typename DataEnum,
          typename std::enable_if_t<std::is_enum_v<DataEnum>, int> = 0>
auto enum_to_string(DataEnum const &data_enum) -> std::string_view;

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
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void insert(Storable const &storable);

/**
 * @brief Retrieves all database objects that match the name that is passed in
 * @param name The name of the object being retrieved fro the database
 *
 * Retrieves all objects of the type requested that contain that name. Does
 * not guarantee that the objects exist. This will either return an std
 * optional with nothing in it, a single object, or a vector.
 *
 * SELECT * from table;
 *
 * Usage:
 *
 * auto all_food = database::utils::retrieve_all<food::Food>();
 *
 * if(all_food) {
 *  // do something
 *  }
 */
template <typename Storable,
          typename std::enable_if_t<
              std::is_base_of_v<database::Storable, Storable>, int> = 0>
auto retrieve_all() -> std::optional<std::vector<Storable>>;

} // namespace utils
} // namespace database

#include "utils.tpp"
