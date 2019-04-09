/**
 * @file food.cpp
 * @author Manuel G. Meraz
 * @date 03/29/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 *        food
 *
 */

#include "database/Data.hpp"
#include "food/Food.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

//! @copydoc food::Food::get_data()
const database::Data food::Food::get_data() const {
  database::Data data;
  data.table_name = "Food";

  // Will recycle this column to build other columns
  database::Column column;

  // This column info is only used for creating a new table
  // The database will generate a primary key value for the entries
  column.name = data.table_name + "_id";
  column.value = "";
  column.data_type = database::DataType::INTEGER;
  column.constraint = database::Constraint::PRIMARY_KEY;
  data.columns.emplace_back(column);

  // The name of the table needs to be in single quotes for the SQL command
  column.name = "name";

  std::stringstream quoted_name;
  quoted_name << "'" << this->name() << "'";
  column.value = quoted_name.str();

  column.data_type = database::DataType::TEXT;

  // The rest of the columns from hereon will be NOT NULL constraint
  column.constraint = database::Constraint::NOT_NULL;

  data.columns.emplace_back(column);

  // The next 4 columns will all be REAL
  column.data_type = database::DataType::REAL;

  const auto macronutrients = this->macronutrients();

  column.name = "fat";
  column.value = std::to_string(macronutrients.fat());
  data.columns.emplace_back(column);

  column.name = "carbohydrate";
  column.value = std::to_string(macronutrients.carbohydrate());
  data.columns.emplace_back(column);

  column.name = "fiber";
  column.value = std::to_string(macronutrients.fiber());
  data.columns.emplace_back(column);

  column.name = "protein";
  column.value = std::to_string(macronutrients.protein());
  data.columns.emplace_back(column);

  return data;
}

//! @copydoc food::Food::set_data(const database::Data &data)
void food::Food::set_data(const database::Data &data) {
  std::unordered_map<std::string_view, std::string_view> organized_data;

  for (const auto &column : data.columns) {
    organized_data[column.name] = column.value;
  }

  this->name_ = organized_data["name"];

  std::string value(organized_data["fat"]);
  size_t size = value.size();
  const auto fat = std::stod(value, &size);

  value = std::string{organized_data["carbohydrate"]};
  size = value.size();
  const auto carbohydrate = std::stod(value, &size);

  value = std::string{organized_data["fiber"]};
  size = value.size();
  const auto fiber = std::stod(value, &size);

  value = std::string{organized_data["protein"]};
  size = value.size();
  const auto protein = std::stod(value, &size);

  this->macronutrients_ = Macronutrients(
      Fat(fat), Carbohydrate(carbohydrate, Fiber(fiber)), Protein(protein));
}

//! @copydoc food::Food::str()
std::string food::Food::str() const {
  std::stringstream ss;
  ss << this->name();

  const auto delimeter = "|";
  const auto macronutrients = this->macronutrients();
  ss << delimeter << macronutrients.fat();
  ss << delimeter << macronutrients.carbohydrate();
  ss << delimeter << macronutrients.fiber();
  ss << delimeter << macronutrients.protein();

  return ss.str();
}
