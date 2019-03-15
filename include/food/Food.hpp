/**
 * @file food.hpp
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
#include <map>
#include <string>
#include <utility>
#include <variant>

/**
 * @brief The food class stores all macronutrient and micronutrient data for any
 *				food
 */
class Food : public Storable {
public:
  Food() = default;

  /**
   * @param macros The macronutrients the food contains
   * @param food_name The name of the food
   */
  Food(const Macronutrients &macros, const std::string &food_name)
      : macronutrients_{macros}, name_{food_name} {}

  /**
   * @brief Copy constructor for lvalues reference
   * @param f The food to be copied
   */
  Food(const Food &f) = default;

  /**
   * @brief Move constructor for rvalue reference
   * @param f The food to be moved
   */
  Food(Food &&f) = default;

  /**
   * @brief Copy assignment operator
   * @param f The food to be copied
   */
  Food &operator=(const Food &f) = delete;

  /**
   * @brief Move assignment operator
   * @param f The food to be moved
   */
  Food &operator=(Food &&f) = delete;

  /**
   * @brief All data will be retrieved from a storable object using this
   *				function.
   *
   * @return A pair containing the column where the data will be stored
   *				 and the data itself.
   */
  std::map<std::string, std::string> get_data() const override;

  /**
   * @return Returns the macronutrients of the food
   */
  const Macronutrients macronutrients() const { return macronutrients_; }

  /**
   * @return Returns the name of the food
   */
  const std::string name() const { return name_; }

  ~Food() = default;

private:
  /**
   *  @brief The macronutrients of the food
   */
  const Macronutrients macronutrients_;

  /**
   *  @brief The name of the food
   */
  const std::string name_;
};

#endif /* FOOD_FOOD_HPP */
