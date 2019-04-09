/**
 * @file macronutrients.hpp
 * @author Manuel G. Meraz
 * @date 03/12/2019
 * @brief Contains the Macronutrients class and related helper classes
 * food
 *
 */

#ifndef FOOD_MACRONUTRIENTS_HPP
#define FOOD_MACRONUTRIENTS_HPP
#include <iostream>
#include <type_traits>

/**
 * @brief Organizes all food related classes and utilities
 */
namespace food {
/**
 * @brief Stores the fat content of a food
 */
struct Fat {
  Fat() : quantity{0} {}
  /**
   * @param quantity The quantiy of fat in grams per 100g of food
   */
  explicit Fat(const double quantity) : quantity{quantity} {};

  /**
   *  @brief The quantiy of fat in grams per 100g of food
   */
  double quantity;
};

/**
 * @brief Stores the fiber content of a food
 */
struct Fiber {
  Fiber() : quantity{0} {}
  /**
   * @param quantity The quantity of fiber in grams per 100g of food
   */
  explicit Fiber(const double quantity) : quantity{quantity} {}

  /**
   * @brief quantity The quantity of fiber in grams per 100g of food
   */
  double quantity;
};

/**
 * @brief Stores the carbohydrate content of a food
 */
struct Carbohydrate {
  Carbohydrate() : quantity_carb{0}, quantity_fiber{0} {}
  /**
   * @param total_carb The total carbohydrate in grams per 100g of food
   */
  explicit Carbohydrate(const double total_carb)
      : quantity_carb(total_carb), quantity_fiber{0} {}

  /**
   * @param total_carb The total carbohydrate in grams per 100g of food
   * @param fiber The total fiber in grams per 100g of food
   */
  explicit Carbohydrate(const double total_carb, const Fiber &fiber)
      : quantity_carb{total_carb}, quantity_fiber(fiber.quantity) {}

  /**
   * @brief The total carbohydrate in grams per 100g of food
   */
  double quantity_carb;

  /**
   *  @brief The total fiber in grams per 100g of food
   */
  double quantity_fiber;
};

/**
 * @brief Stores the protein content of a food
 */
struct Protein {
  Protein() : quantity{0} {}
  /**
   * @param protein The protein in grams per 100g of food
   */
  explicit Protein(const double quantity) : quantity{quantity} {};

  /**
   *  @brief The protein content of the food
   */
  double quantity;
};

/**
 * @brief The macronutrients class stores all macronutrient data to be stored in
 *a Food object
 */
class Macronutrients {
public:
  Macronutrients() : fat_{0}, carbohydrate_{0}, fiber_{0}, protein_{0} {}

  /**
   * @brief The classes passed in to this class are strongly typed classes
   *        to help illustrate the data being passed in.
   *
   * The classes passed in to this class are strongly typed classes
   * to help illustrate the data being passed in. All data passed in
   * is in gramss per 100g of the food
   *
   *
   *
   * @param fat The fat content of the food
   * @param carb The carbohydrate content of the food. Pass by value.
   * @param protein The protein content of the food
   */
  Macronutrients(const Fat &fat, const Carbohydrate carb,
                 const Protein &protein)
      : fat_{fat.quantity}, carbohydrate_{carb.quantity_carb},
        fiber_{carb.quantity_fiber}, protein_{protein.quantity} {}

  /**
   * @brief Copy constructor for lvalues reference
   * @param macros The macros to be copied
   */
  Macronutrients(const Macronutrients &macros) = default;

  /**
   * @brief Move constructor for rvalue reference
   * @param macros The macros to be moved
   */
  Macronutrients(Macronutrients &&macros) noexcept = default;

  /**
   * Copy assignment operator
   * @param macros The macros to be copied
   */
  Macronutrients &operator=(const Macronutrients &macros) = default;

  /**
   * @brief Move assignment operator
   * @param macros The macros to be moved
   */
  Macronutrients &operator=(Macronutrients &&macros) noexcept = default;

  /**
   * @return The quantity of fat
   */
  double fat() const { return fat_; }

  /**
   * @return The quantity of carbohydrate
   */
  double carbohydrate() const { return carbohydrate_; }

  /**
   * @return The quantity of fiber
   */
  double fiber() const { return fiber_; }

  /**
   * @return The quantity of protein
   */
  double protein() const { return protein_; }

  ~Macronutrients() = default;

private:
  /**
   *  @brief The fat in grams per 100g of food
   */
  double fat_;

  /**
   *  @brief The carbohydrate in grams per 100g of food
   */
  double carbohydrate_;

  /**
   *  @brief The fiber in grams per 100g of food
   */
  double fiber_;

  /**
   *  @brief The protein in grams per 100g of food
   */
  double protein_;
};
} // namespace food

#endif /* FOOD_MACRONUTRIENTS_HPP */
