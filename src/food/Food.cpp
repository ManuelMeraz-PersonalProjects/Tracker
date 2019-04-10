/**
 * @file food.cpp
 * @author Manuel G. Meraz
 * @date 03/29/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 *        food
 *
 */

#include "database/Data.hpp"
#include "database/utils.hpp"
#include "food/Food.hpp"
#include <range/v3/all.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

//! @copydoc food::Food::get_data()
auto food::Food::get_data() const -> database::Data const
{
  database::Data data;
  data.table_name = "Food";

  // Food ID|name|fat|carbohydrate|fiber|protein
  data.schema.reserve(6);

  // The properties of a single column;
  database::ColumnProperties column_properties;

  // Food_id column begin
  column_properties.name = data.table_name + "_id";
  column_properties.data_type = database::DataType::INTEGER;
  column_properties.constraint = database::Constraint::PRIMARY_KEY;
  data.schema.emplace_back(column_properties);

  std::vector<database::Row::row_data_t> new_row;
  new_row.reserve(6);

  // std::variant to hold multiple data types. Defined in Data.hpp.
  database::Row::row_data_t row_data = 0;
  if (int count = database::utils::count_rows(data.table_name)) {
    row_data = count + 1;
  }
  new_row.emplace_back(row_data);

  // name column Begin
  // The name of the table needs to be in single quotes for the SQL command
  column_properties.name = "name";
  column_properties.data_type = database::DataType::TEXT;

  // The rest of the columns from hereon will be NOT NULL constraint
  column_properties.constraint = database::Constraint::NOT_NULL;
  data.schema.emplace_back(column_properties);

  std::stringstream quoted_name;
  quoted_name << "'" << this->name() << "'";
  row_data = quoted_name.str();
  new_row.emplace_back(row_data);

  // fat, carbohydrate, fiber, and protein columns begin
  // The next 4 columns will all be REAL
  column_properties.data_type = database::DataType::REAL;

  auto const macronutrients = this->macronutrients();

  column_properties.name = "fat";
  data.schema.emplace_back(column_properties);
  row_data = macronutrients.fat();
  new_row.emplace_back(row_data);

  column_properties.name = "carbohydrate";
  data.schema.emplace_back(column_properties);
  row_data = macronutrients.carbohydrate();
  new_row.emplace_back(row_data);

  column_properties.name = "fiber";
  data.schema.emplace_back(column_properties);
  row_data = macronutrients.fiber();
  new_row.emplace_back(row_data);

  column_properties.name = "protein";
  data.schema.emplace_back(column_properties);
  row_data = macronutrients.protein();
  new_row.emplace_back(row_data);

  data.rows.emplace_back(database::Row{new_row});

  return data;
}

//! @copydoc food::Food::set_data(database::Data const &data)
void food::Food::set_data(std::vector<database::ColumnProperties> const &schema,
                          database::Row const &row)
{
  std::unordered_map<std::string_view, database::Row::row_data_t>
      organized_data;

  auto data = row.row_data;
  for (auto const &[first, second] : ranges::view::zip(schema, data)) {
    organized_data[first.name] = second;
  }

  this->name_ = std::get<std::string>(organized_data["name"]);

  double const fat = std::get<double>(organized_data["fat"]);
  double const carbohydrate = std::get<double>(organized_data["carbohydrate"]);
  double const fiber = std::get<double>(organized_data["fiber"]);
  double const protein = std::get<double>(organized_data["protein"]);

  this->macronutrients_ = Macronutrients(
      Fat(fat), Carbohydrate(carbohydrate, Fiber(fiber)), Protein(protein));
}

//! @copydoc food::Food::str()
auto food::Food::str() const -> std::string
{
  std::stringstream ss;
  ss << this->name();

  auto const delimeter = "|";
  auto const macronutrients = this->macronutrients();
  ss << delimeter << macronutrients.fat();
  ss << delimeter << macronutrients.carbohydrate();
  ss << delimeter << macronutrients.fiber();
  ss << delimeter << macronutrients.protein();

  return ss.str();
}
