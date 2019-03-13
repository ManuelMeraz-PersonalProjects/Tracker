/**
 * @file macronutrients.hpp
 * @author Manuel G. Meraz
 * @date 03/11/2019
 * @brief Contains the Macronutrients class and related helper classes
 * food
 *
 */

#ifndef FOOD_MACRONUTRIENTS_HPP
#define FOOD_MACRONUTRIENTS_HPP

/**
 * Stores the fat content of a food
 */
struct Fat {
  /**
   * @param f The fat content of the food
   */
  explicit Fat(double f) : fat{f}{};

  /**
   *  The fat content of the food
   */
  const double fat;
};

/**
 * Stores the fiber content of a food
 */
struct Fiber {
  /**
   * @param f The fiber content of the food
   */
  explicit Fiber(double f) : fiber{f} {}

  /**
   * The total fiber content of the food
   */
  const double fiber;
};

/**
 * Stores the carbohydrate content of a food
 */
struct Carbohydrate {
  /**
   * @param c The total carbohydrate content of the food
   */
  explicit Carbohydrate(double tc) : total_carb(tc), fiber{0}{};

  /**
   * @param tc The total carbohydrate content of the food
   * @param f The fiber content of the food
   */
  explicit Carbohydrate(double tc, const Fiber &f) : total_carb{tc}, fiber{f}{};

  /**
   *  The total carb content of the food
   */
  const double total_carb;

  /**
   *  The fiber content of the food
   */
  const Fiber fiber;
};

struct Protein {
  /**
   * Stores the protein content of a food
   * @param p The protein content of the food
   */
  explicit Protein(double p) : protein{p}{};

  /**
   *  The protein content of the food
   */
  const double protein;
};

/**
 * The macronutrients class stores all macronutrient data to be stored in a Food
 * object
 */
class Macronutrients {
public:
  Macronutrients() : fat{0}, carb{0}, protein{0} {}

  /**
   * The classes passed in to this class are strongly typed classes
   * to help illustrate the data being passed in.
   *
   * @param f The fat content of the food
   * @param c The carbohydrate content of the food. Pass by value.
   * @param p The protein content of the food
   */
  Macronutrients(const Fat &f, const Carbohydrate c, const Protein &p)
      : fat{f}, carb{c}, protein{p} {}

  /**
   * Copy constructor for lvalues reference
   * @param macros The macros to be copied
   */
  Macronutrients(const Macronutrients &macros) = default;

  /**
   * Move constructor for rvalue reference
   * @param macros The macros to be moved
   */
  Macronutrients(Macronutrients &&macros) = default;

  /**
   * Copy assignment operator
   * @param macros The macros to be copied
   */
  Macronutrients &operator=(const Macronutrients &macros) = delete;

  /**
   * Move assignment operator
   * @param macros The macros to be moved
   */
  Macronutrients &operator=(Macronutrients &&macros) = delete;

  /**
   * All data will be retrieved from a storable object using this function.
   * @return This A pair containing the column where the data will be store
   *				 and the data itself.
   */
  // std::stack<std::pair<std::string, std::variant<double, std::string>>>
  // get_data() const override = delete;

  ~Macronutrients() = default;

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

#endif /* FOOD_MACRONUTRIENTS_HPP */
