from food_utils import Food, Macronutrients, Serving, food_utils

if __name__ == '__main__':
    serving = Serving('g', 100)
    macros = Macronutrients(17, 1, 1, 0, 1)
    food = Food("hot pocket", macros, serving)
    print(food)

    food_utils.create_food_table()

    food_utils.insert_food(food)
    d_food = food_utils.get_food("hot pocket")
    print(d_food)

    food.calories = 18
    food_utils.update_food(food)
    d_food = food_utils.get_food("hot pocket")
    print(d_food)
