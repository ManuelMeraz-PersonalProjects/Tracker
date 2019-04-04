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
#include <queue>
#include <sstream>
#include <string>
#include <utility>

namespace food {

/**
 * @brief The food class stores all macronutrient and micronutrient data for any
 *				food
 */
template <
    typename Number = unsigned int, class Macronutrients = Macronutrients<>,
    typename std::enable_if_t<
        std::is_arithmetic_v<Number> && std::is_class_v<Macronutrients>, int> =
        0>
class Food : public Storable {
public:
  Food() = default;

  /**
   * @param macros The macronutrients the food contains
   * @param food_name The name of the food
   */
  Food(const Macronutrients &macros, std::string food_name)
      : macronutrients_{macros}, name_{std::move(food_name)} {}

  /**
   * @param macros The macronutrients the food contains
   * @param food_name The name of the food
   *
   * This constructor will typically be used to create food objects built by
   * database utils. Enable only if the types being passed in are all the right
   * classes.
   */
  template <class Fat, class Carbohydrate, class Fiber, class Protein,
            typename std::enable_if_t<
                !std::is_same_v<Macronutrients, Fat> && std::is_class_v<Fat> &&
                    std::is_class_v<Carbohydrate> && std::is_class_v<Fiber> &&
                    std::is_class_v<Protein>,
                int> = 0>
  Food(const Fat &fat, const Carbohydrate &carbohydrate, const Fiber &fiber,
       const Protein &protein, std::string food_name)
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
   *				function.
   *
   * @return A pair containing the column where the data will be stored
   *				 and the data itself.
   */
  const database::Data get_data() const override {

    database::Data data;

    data.table_name = "food";

    database::Column column;

    // This column info is only used for creating a new table
    // The database will generate a primary key value for the entries
    column.name = "food_id";
    column.value = "";
    column.data_type = database::DataType::INTEGER;
    column.constraint = database::Constraint::PRIMARY_KEY;
    data.columns.emplace_back(column);

    // The name of the table needs to be in single quotes for the SQL command
    std::stringstream quoted_name;
    quoted_name << "'" << this->name() << "'";

    column.name = "name"; // name column for food
    column.value = quoted_name.str();
    column.data_type = database::DataType::TEXT;

    // The rest of the columns from hereon will be NOT NULL constraint
    column.constraint = database::Constraint::NOT_NULL;

    data.columns.emplace_back(column);

    // The next 4 columns will all be REAL
    column.data_type = database::DataType::REAL;

    column.name = "fat";
    column.value = std::to_string(this->macronutrients().fat());
    data.columns.emplace_back(column);

    column.name = "carbohydrate";
    column.value = std::to_string(this->macronutrients().carbohydrate());
    data.columns.emplace_back(column);

    column.name = "fiber";
    column.value = std::to_string(this->macronutrients().fiber());
    data.columns.emplace_back(column);

    column.name = "protein";
    column.value = std::to_string(this->macronutrients().protein());
    data.columns.emplace_back(column);

    return data;
  }

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
  const Macronutrients macronutrients_;

  /**
   *  @brief The name of the food
   */
  const std::string name_;
};
} // namespace food

#endif /* FOOD_FOOD_HPP */
