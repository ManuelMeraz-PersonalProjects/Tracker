/**
 * \file utils.h
 * \author Manuel G. Meraz
 * \brief Utility functions and objects for databasing
 */

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include <database/Database.hpp>
#include <database/database.hpp>
#include <database/storable.hpp>

namespace database {
/**
 *  Utility functions to store, retrieve, and manipulate objects in database.
 */
namespace utils {

template <typename Storable> 
void store(const &Storable storable) {
  const auto &data = storable.get_data();
}

template <typename Storable, typename Property>
auto retrieve(Type type, Property property) = delete;

} // namespace utils

} // namespace database

#endif /* DATABASE_UTILS_HPP */
