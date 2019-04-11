#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <iostream>

auto main() -> int
{
  food::Macronutrients macros(food::Fat(10),
                              food::Carbohydrate(10, food::Fiber(10)),
                              food::Protein(10));

  food::Food taco("tacos", macros);
  database::utils::insert(taco);

  if (auto all_food = database::utils::retrieve_all<food::Food>()) {
    for (auto &food : *all_food) {
      std::cout << food.str() << std::endl;

      auto macros = food.macronutrients();
      macros.set_protein(25.67);
      macros.set_fiber(3133717397219);
      food.set_macronutrients(macros);

      database::utils::update(food);
    }
  }

  if (auto all_food = database::utils::retrieve_all<food::Food>()) {
    for (auto const &food : *all_food) {
      std::cout << food.str() << std::endl;
    }
  }

  database::utils::drop_table<food::Food>();
  return 0;
}
