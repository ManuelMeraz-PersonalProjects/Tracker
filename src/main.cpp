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

  if (auto entries = database::utils::retrieve<food::Food>()) {
    for (const auto &food : *entries) {
      std::cout << food.str() << std::endl;
    }
  }
  return 0;
}
