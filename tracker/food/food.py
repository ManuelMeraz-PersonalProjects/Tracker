#!/usr/binenv python3


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


class Macronutrients:
    def __init__(self, calories, fat, carb, fiber, protein):
        """
        The macronutrients of the food in ascending order as if being read
        from a nutritional label. The value that is being passed in is the
        grams of fat, carb, etc for its serving size.

        @param calories: The calories for the serving (kcals)
        @type calories: real

        @param fat: The fat for the serving (g)
        @type fat: real

        @param carb: The carbohydrates for the serving (g)
        @type carb: real

        @param fiber: The fiber for the serving (g)
        @type fiber: real

        @param protein: The protein for the serving (g)
        @type protein: real
        """
        self.calories = calories
        self.fat = fat
        self.carb = carb
        self.fiber = fiber
        self.protein = protein


class Micronutrients:
    # TODO(manny): add in micros
    pass


class Serving:
    unit_types = ['G', 'OZ', 'LBS']
    """ The unit types we can handle """

    def __init__(self, unit, size, second_size=0):
        """
        The serving for the food being input to the database.

        @param unit:  The unit type of the serving (e.g. g, oz)
        @type  unit:  text

        @param size:  The quantity of the serving
        @type  size:  real

        @param second_size: The secondary quantity of the serving (e.g. lbs oz)
        @type: real

        """

        if unit.upper() not in Serving.unit_types:
            raise TypeError("""First argument must be a string of unit
                             in this list""" + str(Serving.unit_types))

        try:
            # Make sure they're numbers
            size + second_size + 1
        except TypeError:
            raise TypeError("Values must be numbers")

        self.size = size
        self.unit = unit
        self.second_size = second_size
