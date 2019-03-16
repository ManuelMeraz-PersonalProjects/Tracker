/**
 * \file utils.h
 * \author Manuel G. Meraz
 * \brief Utility functions and objects for databasing
 */

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include "database/Database.hpp"
#include "database/Storable.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace database {
/**
 *  Utility functions to store, retrieve, and manipulate objects in database.
 */
namespace utils {

template <typename Storable> void store(const Storable &storable) {
  auto data = storable.get_data();

  std::stringstream sql_command;

  auto table_name = data.front().second;
	data.pop();

  sql_command << "INSERT INTO " << table_name << "(\n";

  std::stringstream column_values;
  column_values << "VALUES\n(\n";

  std::stringstream column_names;
  const auto append_values = [&column_names, &column_values](const auto &pair) {
    const std::string column_name = pair.first;
    const std::string column_value = pair.second;

    column_names << column_name << ",\n";
    column_values << column_value << ",\n";
  };

  while (data.size() > 1) {
    append_values(data.front());
		data.pop();
  }

  auto last_data = data.front();
	data.pop();

  auto last_column = last_data.first;
  auto last_value = last_data.second;
  column_names << last_column << ")\n";
  column_values << last_value << ")\n";

  sql_command << column_names.str() << column_values.str() << ";";
  std::cout << sql_command.str() << std::endl;
}

// template <typename Storable, typename Property>
// auto retrieve(Type type, Property property) = delete;

} // namespace utils

} // namespace database

#endif /* DATABASE_UTILS_HPP */
