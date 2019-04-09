/**
 * @file Food.hpp
 * @author Manuel G. Meraz
 * @date 03/11/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 * food
 *
 */

#ifndef FOOD_FOOD_HPP
#define FOOD_FOOD_HPP

#include "database/Storable.hpp"
#include "food/Macronutrients.hpp"
#include "soci.h"
#include <string>

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
  Food() = default;

  /**
   * @param macros The macronutrients the food contains
   * @param food_name The name of the food
   */
  Food(const Macronutrients &macros, std::string food_name)
      : macronutrients_{macros}, name_{std::move(food_name)} {}

  /**
   * @param fat The fat in in grams of fat per 100g
   * @param carbohydrate The carbohydrate in in grams of carbohydrate per 100g
   * @param fiber The fiber in in grams of fiber per 100g
   * @param protein The protein in in grams of protein per 100g
   * @param food_name The name of the food
   *
   * This constructor will typically be used to create food objects built by
   * database utils. Enable only if the types being passed in are all the right
   * classes.
   */
  Food(const double &fat, const double &carbohydrate, const double &fiber,
       const double &protein, std::string food_name)
      : macronutrients_(fat, carbohydrate, fiber, protein), name_{std::move(
                                                                food_name)} {}

  /**
   * @brief Copy constructor for lvalues reference
   * @param f The food to be copied
   */
  Food(const Food &f) = default;

  /**
   * @brief Move constructor for rvalue reference
   * @param f The food to be moved
   */
  Food(Food &&f) noexcept = default;

  /**
   * @brief Copy assignment operator
   * @param f The food to be copied
   */
  Food &operator=(const Food &f) = default;

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
  const database::Data get_data() const override;

  /**
   * @return Returns the macronutrients of the food
   */
  const Macronutrients macronutrients() const { return macronutrients_; }

  /**
   * @return Returns the name of the food
   */
  const std::string name() const { return name_; }

  ~Food() override = default;

private:
  /**
   *  @brief The macronutrients of the food
   */
  Macronutrients macronutrients_;

  /**
   *  @brief The name of the food
   */
  std::string name_;
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
  typedef values base_type;

  /*
   * @brief Used to construct an object that is retrieved from the
   *        database.
   *
   * @param v the values retrieved from the database 
   * @param food A reference to the food that will be filled, then
   *             given to the request filled with the right data.
   *
   */
  static void from_base(values const &v, indicator /* ind */,
                        food::Food &food) {

    food::Fat fat(v.get<double>("fat"));
    food::Carbohydrate carbohydrate(v.get<double>("carbohydrate"));
    carbohydrate.quantity_fiber = v.get<double>("fiber");
    food::Protein protein(v.get<double>("protein"));

    food::Macronutrients macros(fat, carbohydrate, protein);
    auto food_name(v.get<std::string>("name"));

    food = food::Food(macros, food_name);
  }

  /*
   * @brief Used to construct an object that is given to the
   *        database.
   *
   * @param food A reference to the food that will be used to extract data
   *             from, then inserted into the database
   * @param v the values that will be used to insert into the database
   * @param ind Sets states for the data. Used by SOCI.
   *
   */
  static void to_base(const food::Food &food, values &v, indicator &ind) {
    v.set("fat", food.macronutrients().fat());
    v.set("carbohydrate", food.macronutrients().carbohydrate());
    v.set("fiber", food.macronutrients().fiber());
    v.set("protein", food.macronutrients().protein());
    v.set("name", food.name());
    ind = i_ok;
  }
};
} // namespace soci

#endif /* FOOD_FOOD_HPP */
