/**
 * \file macronutrients.hpp
 * \author Manuel G. Meraz
 * \brief The food class stores all macronutrient and micronutrient data for any
 * food
 *
 */

#ifndef FOOD_MACRONUTRIENTS_HPP
#define FOOD_MACRONUTRIENTS_HPP

/**
 * The food class stores all macronutrient and micronutrient data for any
 * food
 */
struct Fat {
  /**
   * Stores the fat content of a food
   * @param f The fat content of the food
   */
  explicit Fat(double f) : fat(f){};

  /**
   *  The fat content of the food
   */
  const double fat;
};

struct Carbohydrate {
  /**
   * Stores the carb content of a food
   * @param c The carbohydrate content of the food
   */
  explicit Carbohydrate(double c) : carb(c){};

  /**
   *  The carb content of the food
   */
  const double carb;
};

struct Protein {
  /**
   * Stores the protein content of a food
   * @param p The protein content of the food
   */
  explicit Protein(double p) : protein(p){};

  /**
   *  The protein content of the food
   */
  const double protein;
};

#endif /* FOOD_MACRONUTRIENTS_HPP */
