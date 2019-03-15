/**
 * @file food.cpp
 * @author Manuel G. Meraz
 * @date 03/11/2019
 * @brief The food class stores all macronutrient and micronutrient data for any
 *				food
 *
 */

#include "food/Food.hpp"

//! @copydoc Food::get_data()
std::map<std::string, std::string> Food::get_data() const {
	std::map<std::string, std::string> data;
	data["table"] = "food";
	data["name"] = this->name();
	data["fat"] = std::to_string(this->macronutrients().fat());
	data["carbohydrate"] = std::to_string(this->macronutrients().carb());
	data["fiber"] = std::to_string(this->macronutrients().fiber());
	data["protein"] = std::to_string(this->macronutrients().protein());
	return data;
}
