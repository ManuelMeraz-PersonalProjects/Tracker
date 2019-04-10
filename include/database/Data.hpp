/**
 * @file Data.hpp
 * @author Manuel G. Meraz
 * @date 03/29/2019
 * @brief The container for all data to be stored into a database
 *
 */

#pragma once

#include <ctime>

#include <string>
#include <variant>
#include <vector>

/**
 * @brief Organizes all databasing related classes and functions
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
 * @brief The column properties for a column in a table. A group of these
 *        represents a schema.
 */
struct ColumnProperties {
  /**
   * @brief The name of the column
   */
  std::string name;

  /**
   * @brief The type of data to be stored in the database (e.g. REAL, INTEGER,
   *        TEXT, etc)
   */
  DataType data_type;

  /**
   * @brief The constraint of the data when creating the table
   *        (e.g. PRIMARY KEY, UNIQUE, NOT NULL, or CHECK).
   */
  Constraint constraint;
};

/**
 * @brief A row of variant data
 */
struct Row {
  /**
   * @brief The following data types are the expected types to be received from
   *        the SOCI library when retrieving data
   */
  using row_data_t = std::variant<std::string, std::tm, double, int, long long,
                                  unsigned long long>;

  /**
   * @brief The following data types are the expected types to be received from
   *        the SOCI library when retrieving data
   */
  std::vector<row_data_t> row_data;
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
   * @brief The schema of the table
   */
  std::vector<ColumnProperties> schema;

  /**
   * @brief Each row contains the raw variant data in the same
   *        order as the schema
   */
  std::vector<Row> rows;
};

} // namespace database
