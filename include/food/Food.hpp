/**
 * \file food.hpp
 * \author Manuel G. Meraz
 * \brief The food class stores all macronutrient and micronutrient data for any
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
   * These classes passed in to this class are stringly typed classes
   * to help illustrate the data being passed in.
   *
   * @param f The fat content of the good
   * @param c The carbohydrate content of the food
   * @param p The protein content of the food
   */
  Food(const Fat &f, const Carbohydrate &c, const Protein &p)
      : fat(f), carb(c), protein(p) {}

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
   *  The fat content of the food
   */
  const Fat fat;

  /**
   *  The carbohydrate content of the food
   */
  const Carbohydrate carb;

  /**
   *  The protein content of the food
   */
  const Protein protein;
};

#endif /* FOOD_FOOD_HPP */
