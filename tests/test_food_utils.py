#!/usr/bin/python

import unittest
from context import food_utils
from food_utils import Food, Macronutrients, Serving


class TestFoodUtils(unittest.TestCase):
    def setUp(self):
        food_utils.create_food_db()

    def tearDown(self):
        food_utils.delete_food_db()

    def test_insert_food(self):
        serving = Serving('g', 100)
        macros = Macronutrients(100, 1, 1, 1, 1)
        food = Food("food", macros, serving)
        food_utils.insert_food(food)

        foods = food_utils.get_food("food")
        found_food = False

        for food in foods:
            if food.name == "food":
                found_food = True

                break
        self.assertTrue(found_food)

    def test_get_food_not_in_db(self):
        self.assertEqual(len(food_utils.get_food("food")), 0)


if __name__ == '__main__':
    unittest.main()
