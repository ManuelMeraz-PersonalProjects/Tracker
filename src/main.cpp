#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

// Food, Macronutrients, Fat, Carbohydrate, Fiber, Protein
using namespace food;
namespace utils = database::utils;

auto main() -> int
{
  auto &all_food = utils::retrieve_all<Food>();
  std::cout << "Creating food..." << std::endl;
  for (size_t i = 0; i < 100; ++i) {
    Macronutrients macros(Fat(i), Carbohydrate(i, Fiber(i)), Protein(i));
    utils::make<Food>("tacos", macros);
  }

  std::cout << "Confirm creation in tracker.db" << std::endl;
  std::cout << "Press enter to continue." << std::endl;
  std::cin.ignore();

  std::cout << "Modifying food..." << std::endl;
  for (size_t i = 0; i < 100; ++i) {
    Macronutrients macros(Fat(i * i), Carbohydrate(i * i, Fiber(i * i)),
                          Protein(i * i));
    all_food[i].set_macronutrients(macros);
  }

  std::cout << "Confirm updates in tracker.db" << std::endl;
  std::cout << "Press enter to continue." << std::endl;
  std::cin.ignore();

  std::cout << "Deleting..." << std::endl;
  while (!all_food.empty()) {
    utils::delete_storable(all_food.back());
  }
  std::cout << "Done!" << std::endl;
  return 0;
}
