#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

auto main() -> int
{
  food::Macronutrients macros(food::Fat(10),
                              food::Carbohydrate(10, food::Fiber(10)),
                              food::Protein(10));

  food::Food taco("tacos", macros);
  database::utils::insert(taco);

  if (auto all_food = database::utils::retrieve_all<food::Food>()) {
    for (const auto &food : *all_food) {
      std::cout << food.str() << std::endl;
    }
  }
  return 0;
}
