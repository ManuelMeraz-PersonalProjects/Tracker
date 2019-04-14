#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <iostream>
#include <vector>

template <typename S, typename A> void print(std::vector<S, A> const &all_food)
{
  std::cout << "size: " << all_food.size() << "\n";
  auto delim = "";
  for (auto const &f : all_food) {
    std::cout << delim << f.str();
    delim = ", ";
  }
  std::cout << "\n\n";
}

auto main() -> int
{
  namespace utils = database::utils;

  auto &all_food = utils::retrieve_all<food::Food>();
  std::cout << "Initial: \n";
  print(all_food);

  food::Macronutrients macros(food::Fat(10),
                              food::Carbohydrate(10, food::Fiber(10)),
                              food::Protein(10));

  auto &taco = utils::make<food::Food>("tacos", macros);

  std::cout << "Create: ID: " << taco.id() << "\n";
  print(all_food);
  std::cout << "\n" << taco.str() << std::endl;
  macros.set_fat(25);
  macros.set_protein(3000000);
  taco.set_macronutrients(macros);
  std::cout << "Modify: ID: " << taco.id() << "\n";
  print(all_food);

  if (all_food.size() >= 5) { 
    while(!all_food.empty()) {
      auto& front_food = all_food.front();
      std::cout << "\n To be deleted: " << front_food.str() << std::endl;
      utils::delete_storable(front_food);
      print(all_food);
    }
    std::cout << "Done!\n";
  }
  return 0;
}
