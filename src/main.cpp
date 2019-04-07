#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <iostream>

using food::Carbohydrate;
using food::Fat;
using food::Fiber;
using food::Protein;

void print_food(const food::Food& food) {
  std::cout << food.name() << ": " << food.macronutrients().protein() << std::endl;
}

int main() {
  food::Macronutrients macros(Fat(10), Carbohydrate(10, Fiber(10)),
                              Protein(10));

  food::Food taco(macros, "tacos");
  database::utils::insert(taco);

  const auto food = database::utils::retrieve<food::Food>("tacos");
  print_food(food);
  return 0;
}
