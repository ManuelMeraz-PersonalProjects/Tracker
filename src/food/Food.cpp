/**
 * @file food.cpp
 * @author Manuel G. Meraz
 * @date 03/11/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 *				food
 *
 */

#include "food/Food.hpp"
#include <sstream>

//! @copydoc Food::get_data()
std::queue<std::pair<std::string, std::string>> Food::get_data() const {
  std::queue<std::pair<std::string, std::string>> data;
  auto table_name = std::pair{"table", "food"};
  data.push(table_name);

	std::stringstream quoted_name;
	quoted_name << "'" << this->name() << "'";
  auto food_name = std::pair{"name", quoted_name.str()};
  data.push(food_name);

  auto fat = std::pair{"fat", std::to_string(this->macronutrients().fat())};
  data.push(fat);

  auto carbohydrate = std::pair{
      "carbohydrate", std::to_string(this->macronutrients().carbohydrate())};
  data.push(carbohydrate);

  auto fiber =
      std::pair{"fiber", std::to_string(this->macronutrients().fiber())};
  data.push(fiber);

  auto protein =
      std::pair{"protein", std::to_string(this->macronutrients().protein())};
  data.push(protein);

  return data;
}
