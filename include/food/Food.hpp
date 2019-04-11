/**
 * @file Food.hpp
 * @author Manuel G. Meraz
 * @date 03/11/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 *        food
 */

#pragma once

#include "database/Storable.hpp"
#include "food/Macronutrients.hpp"

#include <soci.h>

#include <string>
#include <string_view>

/**
 * @brief Organizes all food related classes and utilities
 */
namespace food {

/**
 * @brief The food class stores all macronutrient and micronutrient data for any
 *        food
 */
class Food : public database::Storable {
public:
  Food();

  /**
   * @param macros The macronutrients the food contains
   * @param food_name The name of the food
   */
  Food(std::string food_name, Macronutrients macros);

  /**
   * @brief Copy constructor for lvalues reference
   * @param f The food to be copied
   */
  Food(Food const &f) = default;

  /**
   * @brief Move constructor for rvalue reference
   * @param f The food to be moved
   */
  Food(Food &&f) noexcept = default;

  /**
   * @brief Copy assignment operator
   * @param f The food to be copied
   */
  Food &operator=(Food const &f) = default;

  /**
   * @brief Move assignment operator
   * @param f The food to be moved
   */
  Food &operator=(Food &&f) noexcept = default;

  /**
   * @brief All data will be retrieved from a storable object using this
   *        function.
   *
   * @return A struct containing the name of the table to store this data
   *         and a vector of column info. See Data.hpp for more
   *info.
   */
  auto get_data() const -> database::Data const override;

  /**
   * @brief When creating new food objects from data retrieved from the
   *        database, this function will be used to set the data for the
   *        Storable object.
   *
   * @param schema A vector containing the properties of each column that make
   *               up a schema
   *
   * @param data A row of data to set the object data
   * object
   */
  void set_data(std::vector<database::ColumnProperties> const &schema,
                database::Row const &data) override;

  /**
   *  @return The unique ID of this food in the database
   */
  auto id() const -> int override;

  /**
   *  @param A new ID for this object
   */
  void set_id(int id) override;

  /**
   * @return The name of the food
   */
  auto name() const -> std::string const override;

  /**
   * @return The name of the food
   */
  void set_name(std::string_view name) override;

  /**
   * @return string representation of the name and data, the same way sqlite
   *         displays table data
   */
  auto str() const -> std::string override;

  /**
   * @return The macronutrients of the food
   */
  auto macronutrients() const -> Macronutrients const;

  /**
   * @return The macronutrients of the food
   */
  void set_macronutrients(Macronutrients const &macros);

  ~Food() override = default;

private:
  /**
   *  @brief The unique ID of this food in the database
   */
  int id_;

  /**
   *  @brief The name of the food
   */
  std::string name_;

  /**
   *  @brief The macronutrients of the food
   */
  Macronutrients macronutrients_;
};

} // namespace food

/**
 * @brief This is an implementation of object-relational mapping for the
 *        SOCI library. This will be used to retrieve and insert Food
 *        objects directly into the SQL database without needing to manually
 *        give data to the SOCi library.
 *        Source: http://soci.sourceforge.net/doc/master/types/
 */
namespace soci {
template <> struct type_conversion<food::Food> {
  using base_type = values;

  /*
   * @brief Used to construct an object that is retrieved from the
   *        database.
   *
   * @param v the values retrieved from the database
   * @param food A reference to the food that will be filled, then
   *             given to the request filled with the right data.
   */
  static void from_base(values const &v, indicator /* ind */, food::Food &food);

  /*
   * @brief Used to construct an object that is given to the
   *        database.
   *
   * @param food A reference to the food that will be used to extract data
   *             from, then inserted into the database
   *
   * @param v the values that will be used to insert into the database
   * @param ind Sets states for the data. Used by SOCI.
   */
  static void to_base(food::Food const &food, values &v, indicator &ind);
};
} // namespace soci

#include "Food.tpp"
