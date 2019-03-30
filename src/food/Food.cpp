/**
 * @file food.cpp
 * @author Manuel G. Meraz
 * @date 03/29/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 *				food
 *
 */

#include "food/Food.hpp"
#include <sstream>

//! @copydoc Food::get_data()
const database::Data Food::get_data() const {
	database::Data data;

  data.table_name = "food";

	std::stringstream quoted_name;
	quoted_name << "'" << this->name() << "'";

	database::ColumnInfo column_info;
	column_info.value	= quoted_name.str();
	column_info.database_type = "TEXT";

  data.columns.emplace_back("name", column_info);

	column_info.value	= std::to_string(this->macronutrients().fat());
	column_info.database_type = "REAL";

  data.columns.emplace_back("fat", column_info);

	column_info.value = std::to_string(this->macronutrients().carbohydrate());
	column_info.database_type = "REAL";

  data.columns.emplace_back("carbohydrate", column_info);

	column_info.value = std::to_string(this->macronutrients().fiber());
	column_info.database_type = "REAL";

  data.columns.emplace_back("fiber", column_info);

	column_info.value = std::to_string(this->macronutrients().protein());
	column_info.database_type = "REAL";

  data.columns.emplace_back("protein", column_info);

  return data;
}
