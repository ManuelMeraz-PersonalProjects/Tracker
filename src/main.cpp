#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

// Food, Macronutrients, Fat, Carbohydrate, Fiber, Protein
using namespace food;
namespace utils = database::utils;

auto main() -> int
{
  std::cout << "Creating food..." << std::endl;
  for (size_t i = 0; i < 100; ++i) {
    Macronutrients macros(Fat(i), Carbohydrate(i, Fiber(i)), Protein(i));
    utils::make<Food>("tacos", macros);
  }

  auto &all_food = utils::retrieve_all<Food>();
  std::cout << "Deleting..." << std::endl;
  while (!all_food.empty()) {
    utils::delete_storable(all_food.back());
  }
  std::cout << "Done!" << std::endl;
  return 0;
}
