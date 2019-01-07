
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
