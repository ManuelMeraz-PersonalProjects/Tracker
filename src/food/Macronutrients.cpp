/**
 * @file Macronutrients.cpp
 * @author Manuel G. Meraz
 * @date 04/10/2019
 * @brief Contains the Macronutrients class and related helper classes
 *        food
 */

#include "food/Macronutrients.hpp"

food::Fat::Fat() : quantity{0} {}

/// @copydoc food::Fat::Fat(double quantity)
food::Fat::Fat(double quantity) : quantity{quantity} {}

food::Fiber::Fiber() : quantity{0} {}

/// @copydoc food::Fiber::Fiber(double quantity)
food::Fiber::Fiber(double quantity) : quantity{quantity} {}

food::Carbohydrate::Carbohydrate() : quantity_carb{0}, quantity_fiber{0} {}

/// @copydoc food::Carbohydrate::Carbohydrate(double total_carb)
food::Carbohydrate::Carbohydrate(double total_carb)
    : quantity_carb(total_carb), quantity_fiber{0}
{}

/// @copydoc food::Carbohydrate::Carbohydrate(double total_carb, Fiber const
///                                           &fiber))
food::Carbohydrate::Carbohydrate(double total_carb, Fiber const &fiber)
    : quantity_carb{total_carb}, quantity_fiber(fiber.quantity)
{}

food::Protein::Protein() : quantity{0} {}

/// @copydoc food::Protein::Protein(double quantity)
food::Protein::Protein(double quantity) : quantity{quantity} {}

food::Macronutrients::Macronutrients()
    : fat_{0}, carbohydrate_{0}, fiber_{0}, protein_{0}
{}

/// @copydoc  food::Macronutrients::Macronutrients(Fat const &fat, Carbohydrate const &carb,
///                                                Protein const &protein)
food::Macronutrients::Macronutrients(Fat const &fat, Carbohydrate const &carb,
                                     Protein const &protein)
    : fat_{fat.quantity}, carbohydrate_{carb.quantity_carb},
      fiber_{carb.quantity_fiber}, protein_{protein.quantity}
{}

/// @copydoc food::Macronutrients::fat()
auto food::Macronutrients::fat() const -> double
{
  return fat_;
}

/// @copydoc food::Macronutrients::carbohydrate()
auto food::Macronutrients::carbohydrate() const -> double
{
  return carbohydrate_;
}

/// @copydoc food::Macronutrients::fiber()
auto food::Macronutrients::fiber() const -> double
{
  return fiber_;
}

/// @copydoc food::Macronutrients::fiber()
auto food::Macronutrients::protein() const -> double
{
  return protein_;
}
