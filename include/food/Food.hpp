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

#include "food/Macronutrients.hpp"
//#include "database/storable.hpp"
#include <stack>
#include <string>
#include <utility>
#include <variant>

/**
 * The food class stores all macronutrient and micronutrient data for any
 * food
 */
//class Food : public Storable {
class Food {
public:
  /**
   * @param macros The macronutrients the food contains
   * @param name The name of the food
   */
  Food(const Macronutrients& macros, const std::string& food_name)
      : macronutrients{macros}, name{food_name}{}

  /**
   * Copy constructor for lvalues reference
   * @param f The food to be copied
   */
  Food(const Food &f) = default;

  /**
   * Move constructor for rvalue reference
   * @param f The food to be moved
   */
  Food(Food &&f) = default;

  /**
   * Copy assignment operator
   * @param f The food to be copied
   */
  Food &operator=(const Food &f) = delete;

  /**
   * Move assignment operator
   * @param f The food to be moved
   */
  Food &operator=(Food &&f) = delete;

  /**
   * All data will be retrieved from a storable object using this function.
   * @return This A pair containing the column where the data will be store
   *				 and the data itself.
   */
  //std::stack<std::pair<std::string, std::variant<double, std::string>>>
  //get_data() const override = delete;

	virtual ~Food() = default;
 
private:
  /**
   *  The macronutrients of the food
   */
  const Macronutrients macronutrients;

  /**
   *  The name of the food
   */
  const std::string name;
};

#endif /* FOOD_FOOD_HPP */
