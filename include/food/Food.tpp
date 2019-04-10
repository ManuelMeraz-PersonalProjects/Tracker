/**
 * @file Food.tpp
 * @author Manuel G. Meraz
 * @date 04/10/2019
 * @brief Implements the type conversion struct in food/Food.hpp
 */

#pragma once

#include "food/Food.hpp"
#include "food/Macronutrients.hpp"

#include <soci.h>

inline void soci::type_conversion<food::Food>::from_base(values const &v,
                                                         indicator /* ind */,
                                                         food::Food &food)
{
  food::Fat fat(v.get<double>("fat"));
  food::Carbohydrate carbohydrate(v.get<double>("carbohydrate"));
  carbohydrate.quantity_fiber = v.get<double>("fiber");
  food::Protein protein(v.get<double>("protein"));

  food::Macronutrients macros(fat, carbohydrate, protein);
  auto food_name(v.get<std::string>("name"));

  food = food::Food(food_name, macros);
}

inline void soci::type_conversion<food::Food>::to_base(food::Food const &food,
                                                       values &v,
                                                       indicator &ind)
{
  v.set("fat", food.macronutrients().fat());
  v.set("carbohydrate", food.macronutrients().carbohydrate());
  v.set("fiber", food.macronutrients().fiber());
  v.set("protein", food.macronutrients().protein());
  v.set("name", food.name());
  ind = i_ok;
}
