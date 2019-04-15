#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

// Food, Macronutrients, Fat, Carbohydrate, Fiber, Protein
using namespace food;
namespace utils = database::utils;

auto main() -> int
{
  Macronutrients macros(Fat(10), Carbohydrate(10, Fiber(10)), Protein(10));
  auto &taco = utils::make<Food>("tacos", macros);
  std::cout << taco.str() << std::endl;

  utils::delete_storable(taco);
  return 0;
}
