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
 * @param T The template parameter T could be any possible type.
 *
 * Usage:
 * @n std::string type_string = database::utils::type_to_string<food::Food>();
 * @n type_string == "Food" // true
 */
template <typename T> auto type_to_string() -> std::string;

/**
 * @brief Count the number of Storable type in the database
 * @param Storable Any type that is a base of Storable
 *
 * Creates the following SQLite3 command:
 * @n SELECT count(*) from table_name;
 *
 * Usage:
 * @n size_t quantity = database::utils::count_rows<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
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
 * @n create_table<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void create_table(std::vector<ColumnProperties> const &schema);

/**
 * @brief Deletes the Storable table from the database
 * @param Storable Any type that is a base of Storable
 *
 * Creates the following SQLite3 command:
 * DROP TABLE table_name;
 *
 * Usage:
 * drop_table<food::Food>();
 */
template <
    typename Storable,
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void drop_table();

/**
 * @brief Check if Storable table exists in database
 * @param Storable Any type that is a base of Storable
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
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
auto table_exists() -> bool;

/**
 * @brief to_string function for data enum types
 * @param data_enum DataEnum type that is either a constraint type or sql type
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
    typename std::enable_if_t<std::is_base_of_v<Storable, Storable>, int> = 0>
void insert(Storable const &storable);

/**
 * @brief Retrieves all database objects that match the name that is passed in
 * @param Storable The type of storable object being retrieved
 *
 * Retrieves all objects of the type requested that contain that name. Does
 * @n not guarantee that the objects exist. This will either return an std
 * @n optional with nothing in it, or a vector.
 *
 * Creates the following SQLite3 command:
 * @n SELECT * from Storable;
 *
 * Usage:
 * @n auto all_food = database::utils::retrieve_all<food::Food>();
 *
 * @n if(all_food) {
 * @n  // do something
 * @n  }
 */
template <typename Storable,
          typename std::enable_if_t<
              std::is_base_of_v<database::Storable, Storable>, int> = 0>
auto retrieve_all() -> std::optional<std::vector<Storable>>;

} // namespace utils
} // namespace database

#include "utils.tpp"
