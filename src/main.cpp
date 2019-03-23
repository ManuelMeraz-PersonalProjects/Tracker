#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

int main() {
  Macronutrients macros(Fat(10), Carbohydrate(10, Fiber(10)), Protein(10));
  Food food(macros, "tacos");
	database::utils::insert(food);
  return 0;
}
