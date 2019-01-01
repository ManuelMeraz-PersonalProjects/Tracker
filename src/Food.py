"""
File: Food.py
Author: Manuel Meraz
Email: meraz.manuel@gmail.com
Github: https://github.com/manuelmeraz
Description: Classes to handle food database information
"""


class Food:
    def __init__(self, name, macros, serving, micros=None):

        self.name = name
        # implicitly known that serving size will be passed in as cals/100g

        if serving.unit == "g":
            scale = 100/serving.size
        elif serving.unit == "oz":
            serving_in_grams = serving.size * 28
            scale = 100/serving_in_grams
        else:
            serving_in_oz = serving.size * 16 + serving.second_size
            serving_in_grams = serving_in_oz * 28
            scale = 100/serving_in_grams

        self.calories = macros.calories * scale
        self.fat = macros.fat * scale
        self.carb = macros.carb * scale
        self.fiber = macros.fiber * scale
        self.protein = macros.protein * scale

    def _calories_make_sense(self):
        """
        Check if calories passed in make sense by checking if they
        are within a 10% error of the computed calories from the macros
        """
        calculated_calories = 4 * (self.protein + self.carb - self.fiber)
        calculated_calories += 9 * self.fat

        percent_difference = abs((self.calories - calculated_calories))
        percent_difference /= calculated_calories

        if percent_difference > 0.1:
            return False

        return True


class Macronutrients:
    def __init__(self, calories, fat, carb, fiber, protein):
        self.calories = calories
        self.fat = fat
        self.carb = carb
        self.fiber = fiber
        self.protein = protein


class Serving:
    def __init__(self, unit, size, second_size=0):
        """
        @param unit:  The unit type of the serving (e.g. g, oz)
        @type  unit:  text

        @param size:  The quantity of the serving
        @type  size:  real

        @param second_size: The secondary quantity of the serving (e.g. lbs oz)
        @type: real

        """
        self.size = size
        self.unit = unit
        self.second_size = second_size


class Micronutrients:
    # TODO(manny): add in micros
    pass
