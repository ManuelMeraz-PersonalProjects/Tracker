#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <iostream>
#include <vector>

template<typename S, typename A>
void print(std::vector<S, A> const& all_food) {
  std::cout << "\n======= size: " << all_food.size() << " =======\n";
  auto delim = "";
  for(auto const& f:all_food) {
    std::cout << delim << f.str();
    delim = ", ";
  }
  std::cout << "\n======= end =======\n";
}

auto main() -> int
{
  namespace utils = database::utils;

  auto& all_food = utils::retrieve_all<food::Food>();
  food::Macronutrients macros(food::Fat(10),
                              food::Carbohydrate(10, food::Fiber(10)),
                              food::Protein(10));
  print(all_food);

  food::Food &taco = utils::make<food::Food>("tacos", macros);
  print(all_food);
  std::cout << "\n" << taco.str() << std::endl;
  macros.set_fat(25);
  macros.set_protein(3000000);
  taco.set_macronutrients(macros);


  print(all_food);
  if(all_food.size() >= 5) {
    utils::drop_table<food::Food>();
  }
  return 0;
}
