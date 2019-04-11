/**
 * @file Macronutrients.cpp
 * @author Manuel G. Meraz
 * @date 04/10/2019
 * @brief Contains the Macronutrients class and related helper classes
 *        food
 */

#include "food/Macronutrients.hpp"

food::Fat::Fat() : quantity{0} {}

food::Fat::Fat(double quantity) : quantity{quantity} {}

food::Fiber::Fiber() : quantity{0} {}

food::Fiber::Fiber(double quantity) : quantity{quantity} {}

food::Carbohydrate::Carbohydrate() : quantity_carb{0}, quantity_fiber{0} {}

food::Carbohydrate::Carbohydrate(double total_carb)
    : quantity_carb(total_carb), quantity_fiber{0}
{}

food::Carbohydrate::Carbohydrate(double total_carb, Fiber const &fiber)
    : quantity_carb{total_carb}, quantity_fiber(fiber.quantity)
{}

food::Protein::Protein() : quantity{0} {}

food::Protein::Protein(double quantity) : quantity{quantity} {}

food::Macronutrients::Macronutrients()
    : fat_{0}, carbohydrate_{0}, fiber_{0}, protein_{0}
{}

food::Macronutrients::Macronutrients(Fat const &fat, Carbohydrate const &carb,
                                     Protein const &protein)
    : fat_{fat.quantity}, carbohydrate_{carb.quantity_carb},
      fiber_{carb.quantity_fiber}, protein_{protein.quantity}
{}

auto food::Macronutrients::fat() const -> double
{
  return fat_;
}

void food::Macronutrients::set_fat(double fat) {
  this->fat_ = fat;
}

auto food::Macronutrients::carbohydrate() const -> double
{
  return carbohydrate_;
}

void food::Macronutrients::set_carbohydrate(double carbohydrate) {
  this->carbohydrate_ = carbohydrate;
}

auto food::Macronutrients::fiber() const -> double
{
  return fiber_;
}

void food::Macronutrients::set_fiber(double fiber) {
  this->fiber_ = fiber;
}

auto food::Macronutrients::protein() const -> double
{
  return protein_;
}

void food::Macronutrients::set_protein(double protein) {
  this->protein_ = protein;
}
