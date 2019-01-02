from food_utils import Food, Macronutrients, Serving

if __name__ == '__main__':
    serving = Serving('g', 100)
    macros = Macronutrients(17, 1, 1, 0, 1)
    food = Food("hot pocket", macros, serving)

    Food.create_food_table()

    Food.insert_food(food)
    d_food = Food.get_food("hot pocket")
    print(d_food)

    food.calories = 18
    Food.update_food(food)
    d_food = Food.get_food("*")
    print(d_food)
