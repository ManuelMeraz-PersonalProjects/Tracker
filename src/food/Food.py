
class Food:
    def __init__(self, name, macros, serving, micros=None):
        """
        The food class contains all information of a specific food
        that will be input into the database. Contains a few static
        helper functions related to accessing the database.

        @param name:  Name of the food
        @type  name:  text

        @param macros:  Object containing the macronutrients of the food
        @type  macros:  Object of class Macronutrients

        @param serving:  Object containing the serving size and unit of food
        @type  serving:  Object of class Serving

        @param micros:  Object containing the micronutrients
        @type  micros:  Object of class Micronutrients. Default is None.
        """

        self.name = name

        # Everything will be stored in cals/100g in database
        # So we will convert and scale the serving size
        # based off of that

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
        are within a 10% error of the computed calories from the macros.

        Occasionally calorie info is inaccurate, so it is not useful
        off of the nutritonal package.
        """
        calculated_calories = 4 * (self.protein + self.carb - self.fiber)
        calculated_calories += 9 * self.fat

        percent_difference = abs((self.calories - calculated_calories))
        percent_difference /= calculated_calories

        if percent_difference > 0.1:
            return False

        return True

    def __str__(self):
        """
        Print out of object
        """
        name = '\n' + self.name + '\n'
        cals = "Calories: {}\n".format(self.calories)
        fat = "Fat: {}\n".format(self.fat)
        carbs = "Carbs: {}\n".format(self.carb)
        fiber = "Fiber: {}\n".format(self.fiber)
        protein = "Protein: {}\n".format(self.protein)
        str = name + cals + fat + carbs + fiber + protein

        return str

    def __repr__(self):
        """
        Print out of object
        """
        name = '\n' + self.name + '\n'
        cals = "Calories: {}\n".format(self.calories)
        fat = "Fat: {}\n".format(self.fat)
        carbs = "Carbs: {}\n".format(self.carb)
        fiber = "Fiber: {}\n".format(self.fiber)
        protein = "Protein: {}\n".format(self.protein)
        str = name + cals + fat + carbs + fiber + protein

        return str
