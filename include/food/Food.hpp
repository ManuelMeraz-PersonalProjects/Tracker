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
#include <database/utils.hpp>

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
  Food(Food &&f) = default;

  Food &operator=(Food const &f) = default;
  Food &operator=(Food &&f) = default;

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
   *  @return The unique ID of this food in the database
   */
  auto id() const -> int override;

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

  /**
   * @brief Custom allocator that allows database utils to own a vector
   *        of storable objects with private constructors
   */
  struct Allocator : std::allocator<Food> {
    template <class Food, typename... Args>
    void construct(Food *buffer, Args &&... args)
    {
      /**
       * @brief In place new construction of storable by memory pool that is
       *        given
       */
      new (buffer) Food(std::forward<Args>(args)...);
    }

    template <class Food> struct rebind {
      using other = Allocator;
    };
  };

  friend struct Allocator;

private:
  Food() = default;
  Food(Food const &f) = default;

  /**
   * @param id a uniquely generated ID given by database utils
   */
  explicit Food(int id);

  /**
   * @param id a uniquely generated ID given by database utils
   * @param macros The macronutrients the food contains
   * @param food_name The name of the food
   */
  Food(int id, std::string food_name, Macronutrients macros);

  /**
   * @param A schema for this Storable object
   * @param The row of data to construct the object
   */
  Food(std::vector<database::ColumnProperties> const &schema,
       database::Row const &data);

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
