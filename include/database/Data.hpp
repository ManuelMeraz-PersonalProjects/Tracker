/**
 * @file Data.hpp
 * @author Manuel G. Meraz
 * @date 03/29/2019
 * @brief The container for all data to be stored into a database
 *
 */

#ifndef DATABASE_DATA_HPP
#define DATABASE_DATA_HPP

#include <string>
#include <vector>

/**
 * @brief Utility functions to store, retrieve, and manipulate objects in
 */
namespace database {

/**
 * @brief SQL datatypes that could be stored into a database
 *
 * Types with the underscore _ suffix were special keywords that
 * could not be defined.
 */
enum class DataType { REAL, INTEGER, TEXT, NULL_, BLOB };

/**
 * @brief The SQL constraint for column of data when creating a table schema
 *
 */
enum class Constraint { PRIMARY_KEY, UNIQUE, NOT_NULL, CHECK };

/**
 * @The column info for inserting data into a database
 */
struct Column {

  /**
   * @brief The name of the column
   */
  std::string name;

  /**
   * @brief The value that will be stored in this column
   */
  std::string value;

  /**
   * @brief The type of data to be stored in the database (e.g. REAL, INTEGER,
   *				TEXT, etc)
   */
  DataType data_type;

  /**
   * @brief The constraint of the data when creating the table
   *				(e.g. PRIMARY KEY, UNIQUE, NOT NULL, or CHECK).
   */
  Constraint constraint;
};

/**
 * @brief The data to be stored into a database
 */
struct Data {

  /**
   * @brief The table name where the data will be stored
   */
  std::string table_name;

  /**
   * @brief The column info to be stored
   *
   */
  std::vector<Column> columns;
};

} // namespace database

#endif /* DATABASE_DATA_HPP */
