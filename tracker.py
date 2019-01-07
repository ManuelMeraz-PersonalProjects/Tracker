#!/usr/bin/python

import food
# import sys
# import random
# from PySide2 import QtCore, QtWidgets, QtGui

if __name__ == '__main__':
    serving = food.Serving('g', 100)
    macros = food.Macronutrients(17, 1, 1, 0, 1)
    d_food = food.Food("hot pocket", macros, serving)
    print(d_food)

    food.utils.create_food_db()

    food.utils.insert_food(d_food)
    d_food = food.utils.get_food("hot pocket")[0]
    print(d_food)

    d_food.calories = 18
    food.utils.update_food(d_food)
    d_food = food.utils.get_food("hot pocket")
    print(d_food)
