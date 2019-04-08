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
#include <nameof.hpp>
#include <range/v3/all.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

//! @copydoc Food::get_data()
const database::Data food::Food::get_data() const {
  database::Data data;

  // Name with namespace included namespace::ClassName
  data.table_name = nameof::nameof_type<std::decay_t<decltype(*this)>>();

  const auto remove_namespace = [](std::string_view name) {
    auto split_name = name 
      | ranges::view::split(':') 
      | ranges::view::transform([](auto &&rng) { 
          return std::string_view(&*rng.begin(), ranges::distance(rng)); 
        }) 
      | ranges::to_vector;

    return split_name.back();
  };
  
  // namespace::ClassName -> ClassName
  // Can now use class name as table name
  data.table_name = remove_namespace(data.table_name);

  database::Column column;

  // This column info is only used for creating a new table
  // The database will generate a primary key value for the entries
  column.name = data.table_name + "_id";
  column.value = "";
  column.data_type = database::DataType::INTEGER;
  column.constraint = database::Constraint::PRIMARY_KEY;
  data.columns.emplace_back(column);

  // The name of the table needs to be in single quotes for the SQL command
  std::stringstream quoted_name;
  quoted_name << "'" << this->name() << "'";

  // NAMEOF says columns.name is equal to the name of this function
  // column.name = "name";
  column.name = NAMEOF(this->name()); 
  column.value = quoted_name.str();
  column.data_type = database::DataType::TEXT;

  // The rest of the columns from hereon will be NOT NULL constraint
  column.constraint = database::Constraint::NOT_NULL;

  data.columns.emplace_back(column);

  // The next 4 columns will all be REAL
  column.data_type = database::DataType::REAL;

  column.name = NAMEOF(this->macronutrients().fat());
  column.value = std::to_string(this->macronutrients().fat());
  data.columns.emplace_back(column);

  column.name = NAMEOF(this->macronutrients().carbohydrate());
  column.value = std::to_string(this->macronutrients().carbohydrate());
  data.columns.emplace_back(column);

  column.name = NAMEOF(this->macronutrients().fiber());
  column.value = std::to_string(this->macronutrients().fiber());
  data.columns.emplace_back(column);

  column.name = NAMEOF(this->macronutrients().protein());
  column.value = std::to_string(this->macronutrients().protein());
  data.columns.emplace_back(column);

  return data;
}
