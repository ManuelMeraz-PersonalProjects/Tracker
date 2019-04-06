/**
 * @file storable.hpp
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
 * @brief Utility functions to store, retrieve, and manipulate objects in
 *        database.
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
  virtual ~Storable() = default;
};

#endif /* DATABASE_STORABLE_HPP */
