/**
 * @file Storable.hpp
 * @author Manuel G. Meraz
 * @date 03/11/2019
 * @brief The base class that all storable data will inherit from.
 *
 */

#ifndef DATABASE_STORABLE_HPP
#define DATABASE_STORABLE_HPP

#include "database/Data.hpp"
#include <string>

/**
 * @brief Organizes all databasing related classes and functions
 */
namespace database {

/*
 * @brief The base class that all storable data will inherit from.
 *
 */
class Storable {
public:
  /**
   * @brief All data will be retrieved from a storable object using this
   *        function.
   *
   * @return This A pair containing the column where the data will be store
   *         and the data itself.
   */
  virtual const database::Data get_data() const = 0;

  /**
   * @brief When creating new food objects from data retrieved from the
   *        database, this function will be used to set the data for the
   *        Storable object.
   *
   * @param data The data retrieved from the database, most likely from
   *             database::utilsA.
   */
  virtual void set_data(const database::Data &data) = 0;

  /**
   * @return string representation of the name and data, the same way sqlite
   *         displays table data
   */
  virtual std::string str() const = 0;
  virtual ~Storable() = default;
};
} // namespace database

#endif /* DATABASE_STORABLE_HPP */
