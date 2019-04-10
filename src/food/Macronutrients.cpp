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

auto food::Macronutrients::carbohydrate() const -> double
{
  return carbohydrate_;
}

auto food::Macronutrients::fiber() const -> double
{
  return fiber_;
}

auto food::Macronutrients::protein() const -> double
{
  return protein_;
}
