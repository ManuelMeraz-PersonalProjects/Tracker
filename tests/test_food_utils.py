#!/usr/bin/python

import unittest
import os
from context import food
from food import Food, Macronutrients, Serving, utils


class TestFoodUtils(unittest.TestCase):
    def setUp(self):
        utils.create_food_db()

    def tearDown(self):
        utils.delete_food_db()

    def test_insert_and_get_food(self):
        serving = Serving('g', 100)
        macros = Macronutrients(100, 1, 1, 1, 1)
        new_food = Food("food", macros, serving)
        utils.insert_food(new_food)

        foods = utils.get_food("food")
        found_food = False

        for f in foods:
            if f.name == "food":
                found_food = True

                break
        self.assertTrue(found_food)

    def test_get_food_not_in_db(self):
        self.assertEqual(len(utils.get_food("food")), 0)

    def test_serving_first_arg(self):
        self.assertRaises(AttributeError, Serving, 100, 100)

    def test_serving_second_arg(self):
        self.assertRaises(TypeError, Serving, 'g', 'g')

    # def test_macronutrient_args(self):
        # self.assertRaises(TypeError, Macronutrients, 'd', 'd', 'd', 'd', 'd')

    def test_food_args(self):
        self.assertRaises(AttributeError, Food, 99, 99, 99)


class TestFoodUtilsDBFunctions(unittest.TestCase):
    def test_create_food_db(self):
        utils.create_food_db()
        self.assertTrue('food.db' in os.listdir('.'))

    def test_remove_food_db(self):
        utils.delete_food_db()
        self.assertFalse('food.db' in os.listdir('.'))


if __name__ == '__main__':
    unittest.main()
