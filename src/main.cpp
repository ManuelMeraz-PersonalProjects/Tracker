#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

int main() {
   food::Macronutrients macros(food::Fat(10),
   food::Carbohydrate(10, food::Fiber(10)),
   food::Protein(10));

   food::Food taco(macros, "tacos");
   database::utils::insert(taco);

   //database::utils::retrieve<food::Food>();
  return 0;
}
