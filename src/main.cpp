#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

using food::Carbohydrate;
using food::Fat;
using food::Fiber;
using food::Protein;

int main() {
  food::Macronutrients macros(Fat(10), Carbohydrate(10, Fiber(10)), Protein(10));
  food::Food taco(macros, "tacos");
	for(size_t i = 0; i < 100; ++i) {
		database::utils::insert(taco);
	}
  return 0;
}
