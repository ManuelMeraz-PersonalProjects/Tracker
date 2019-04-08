#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <nameof.hpp>
#include <iostream>
#include <string_view>

enum class test { A, B };

int main() {
   food::Macronutrients macros(food::Fat(10),
   food::Carbohydrate(10, food::Fiber(10)),
   food::Protein(10));

   food::Food taco(macros, "tacos");
   database::utils::insert(taco);

   const auto entries = database::utils::retrieve<food::Food>();
   for(const auto& entry:entries) {
     std::cout << entry << std::endl;
   }
   std::cout << "filler: " << NAMEOF_ENUM(test::A) << " :filler" << std::endl;
  return 0;
}
