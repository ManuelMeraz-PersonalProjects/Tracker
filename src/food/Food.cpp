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

//! @copydoc Food::get_data()
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
