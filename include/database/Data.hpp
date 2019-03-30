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
 * @The column info for inserting data into a database
 */
struct ColumnInfo {

  /**
   * @brief The value that will be stored in this column
   */
  std::string value;

  /**
   * @brief The type of data to be stored in the database (e.g. REAL, INTEGER,
   *				TEXT, etc)
   */
  std::string database_type;

  /**
   * @brief When creating a table, whether this data can be null when inserted
   *				(most likely not)
   */
  bool is_null = false;
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
   * @brief The column names along with the column info in no particular order to be stored
   */
  std::vector<std::pair<std::string, ColumnInfo>> columns;
};

} // namespace database

#endif /* DATABASE_DATA_HPP */
