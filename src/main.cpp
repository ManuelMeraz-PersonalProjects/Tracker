#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <string_view>

int main() {
  food::Macronutrients macros(food::Fat(10),
                              food::Carbohydrate(10, food::Fiber(10)),
                              food::Protein(10));

  food::Food taco(macros, "tacos");
  database::utils::insert(taco);

  //if (auto entries = database::utils::retrieve<food::Food>()) {
    //for (const std::string_view &entry : *entries) {
      //std::cout << entry << std::endl;
    //}
  //}
  database::utils::retrieve<food::Food>();
  return 0;
}
