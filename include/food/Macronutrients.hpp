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
 * @brief Stores the fat content of a food
 */
template <typename Number = unsigned int,
          typename std::enable_if_t<std::is_arithmetic_v<Number>, int> = 0>
struct Fat {
  Fat() : quantity{0} {}
  /**
   * @param quantity The quantiy of fat in grams per 100g of food
   */
  explicit Fat(const Number quantity) : quantity{quantity} {};

  /**
   *  @brief The quantiy of fat in grams per 100g of food
   */
  const Number quantity;
};

/**
 * @brief Stores the fiber content of a food
 */
template <typename Number = unsigned int,
          typename std::enable_if_t<std::is_arithmetic_v<Number>, int> = 0>
struct Fiber {
  Fiber() : quantity{0} {}
  /**
   * @param quantity The quantity of fiber in grams per 100g of food
   */
  explicit Fiber(const Number quantity) : quantity{quantity} {}

  /**
   * @brief quantity The quantity of fiber in grams per 100g of food
   */
  const Number quantity;
};

/**
 * @brief Stores the carbohydrate content of a food
 */
template <typename Number = unsigned int,
          typename std::enable_if_t<std::is_arithmetic_v<Number>, int> = 0>
struct Carbohydrate {
  Carbohydrate() : quantity_carb{0}, quantity_fiber{0} {}
  /**
   * @param total_carb The total carbohydrate in grams per 100g of food
   */
  template <typename Fiber = Fiber<>,
            typename std::enable_if_t<std::is_class_v<Fiber>, int> = 0>
  explicit Carbohydrate(const Number total_carb)
      : quantity_carb(total_carb), quantity_fiber{0} {}

  /**
   * @param total_carb The total carbohydrate in grams per 100g of food
   * @param fiber The total fiber in grams per 100g of food
   */
  template <typename Fiber = Fiber<>,
            typename std::enable_if_t<std::is_class_v<Fiber>, int> = 0>
  explicit Carbohydrate(const Number total_carb, const Fiber &fiber)
      : quantity_carb{total_carb}, quantity_fiber(fiber.quantity) {}

  /**
   * @brief The total carbohydrate in grams per 100g of food
   */
  const Number quantity_carb;

  /**
   *  @brief The total fiber in grams per 100g of food
   */
  const Number quantity_fiber;
};

/**
 * @brief Stores the protein content of a food
 */
template <typename Number = unsigned int,
          typename std::enable_if_t<std::is_arithmetic_v<Number>, int> = 0>
struct Protein {
  Protein() : quantity{0} {}
  /**
   * @param protein The protein in grams per 100g of food
   */
  explicit Protein(const Number quantity) : quantity{quantity} {};

  /**
   *  @brief The protein content of the food
   */
  const Number quantity;
};

/**
 * @brief The macronutrients class stores all macronutrient data to be stored in
 *a Food object
 */
template <typename Number = unsigned int,
          typename std::enable_if_t<std::is_arithmetic_v<Number>, int> = 0>
class Macronutrients {
public:
  Macronutrients() : fat_{0}, carbohydrate_{0}, fiber_{0}, protein_{0} {}

  /**
   * @brief The classes passed in to this class are strongly typed classes
   *				to help illustrate the data being passed in.
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
  template <typename Fat = Fat<>, typename Carbohydrate = Carbohydrate<>,
            typename Fiber = Fiber<>, typename Protein = Protein<>,
            typename std::enable_if_t<
                std::is_class_v<Fat> && std::is_class_v<Carbohydrate> &&
                    std::is_class_v<Fiber> && std::is_class_v<Protein>,
                int> = 0>
  Macronutrients(const Fat &fat, const Carbohydrate carb,
                 const Protein &protein)
      : fat_{fat.quantity}, carbohydrate_{carb.quantity_carb},
        fiber_{carb.quantity_fiber}, protein_{protein.quantity} {}

  /**
   * @brief This constructor is used automatically and not meant
   *				to be used by humans, due to reduced
   *readability.
   *
   * This constructor will mainly be used to pass in data
   * from the food database to construct a food object.
   *
   * @param fat The fat content of the food
   * @param carb The carbohydrate content of the food. Pass by value.
   * @param protein The protein content of the food
   */
  Macronutrients(const Number fat, const Number carbohydrate,
                 const Number fiber, const Number protein)
      : fat_{fat}, carbohydrate_{carbohydrate}, fiber_{fiber}, protein_{
                                                                   protein} {}

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
  Number fat() const { return fat_; }

  /**
   * @return The quantity of carbohydrate
   */
  Number carbohydrate() const { return carbohydrate_; }

  /**
   * @return The quantity of fiber
   */
  Number fiber() const { return fiber_; }

  /**
   * @return The quantity of protein
   */
  Number protein() const { return protein_; }

  ~Macronutrients() = default;

private:
  /**
   *  @brief The fat in grams per 100g of food
   */
  const Number fat_;

  /**
   *  @brief The carbohydrate in grams per 100g of food
   */
  const Number carbohydrate_;

  /**
   *  @brief The fiber in grams per 100g of food
   */
  const Number fiber_;

  /**
   *  @brief The protein in grams per 100g of food
   */
  const Number protein_;
};

#endif /* FOOD_MACRONUTRIENTS_HPP */
