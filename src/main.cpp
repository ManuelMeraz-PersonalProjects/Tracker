#include "database/utils.hpp"
#include "food/Food.hpp"           // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <iostream>
#include <vector>

template <typename F>
void handle_all_food(F const &handle, std::vector<food::Food> &all_food);
void print_food(food::Food const &food);
void update_food(food::Food &food);

auto main() -> int
{
  food::Macronutrients macros(food::Fat(10),
                              food::Carbohydrate(10, food::Fiber(10)),
                              food::Protein(10));

  food::Food taco("tacos", macros);
  // Need to create unique ID's if they're only created here
  database::utils::insert(taco);

  if (auto all_food = database::utils::retrieve_all<food::Food>()) {
    handle_all_food(update_food, *all_food);
  }

  if (auto all_food = database::utils::retrieve_all<food::Food>()) {
    handle_all_food(print_food, *all_food);
  }

  auto const delete_food = [](auto &food) {
    database::utils::delete_storable(food);
  };

  if (auto all_food = database::utils::retrieve_all<food::Food>()) {
    std::cout << "Deleting food...\n";
    handle_all_food(delete_food, *all_food);
    std::cout << "Deleted!\n";
  }

  database::utils::drop_table<food::Food>();
  return 0;
}

template <typename F>
void handle_all_food(F const &handle, std::vector<food::Food> &all_food)
{
  for (auto &food : all_food) {
    handle(food);
  }
}

void print_food(food::Food const &food)
{
  std::cout << food.str() << std::endl;
}

void update_food(food::Food &food)
{
  print_food(food);

  auto macros = food.macronutrients();
  macros.set_protein(25.67);
  macros.set_fiber(3133717397219);
  food.set_macronutrients(macros);

  database::utils::update(food);
}
