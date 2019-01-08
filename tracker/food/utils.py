#!/usr/binenv python3

"""
@author: Manuel Meraz
@contact: meraz.manuel@gmail.com
@contact: https://github.com/manuelmeraz
@summary: Classes to handle food database information
"""
import sqlite3
import os
from tracker import food


def create_food_db():
    """
    Creates the food database if it exists.
    """
    conn = sqlite3.connect('food.db')
    cursor = conn.cursor()
    cursor.execute("""CREATE TABLE IF NOT EXISTS food (
                    name text,
                    calories real,
                    fat real,
                    carb real,
                    fiber real,
                    protein real,
                    UNIQUE(name)
                    )""")
    conn.commit()
    conn.close()


def delete_food_db():
    """
    delete the food database if it exists.
    """
    os.remove('food.db')


def get_food(name):
    """
    Returns all results with that name

    @param name: Name of the food
    @type name: text

    @return foods: All foods matching the food name passed in
    @rtype foods: A list of Food objects
    """
    conn = sqlite3.connect('food.db')
    cursor = conn.cursor()

    try:
        cursor.execute("SELECT * FROM food WHERE name=:name", {'name': name})
    except sqlite3.OperationalError:
        print("Food does not exist")
        conn.close()
        return []

    food_data = cursor.fetchall()
    conn.close()

    foods = []

    for data in food_data:
        # Data in databse is in macros/100g
        serving = food.Serving('g', 100)
        macros = food.Macronutrients(data[1], data[2], data[3],
                                     data[4], data[5])

        new_food = food.Food(name, macros, serving)
        foods.append(new_food)

    return foods


def insert_food(food):
    """
    Inserts food into the database

    @param food: A Food object containing all food info
    @type food: Object of class Food
    """
    conn = sqlite3.connect('food.db')
    cursor = conn.cursor()
    data = {'name': food.name,
            'calories': food.calories,
            'fat': food.fat,
            'carb': food.carb,
            'fiber': food.fiber,
            'protein': food.protein}

    try:
        cursor.execute("""INSERT INTO food VALUES (
         :name, :calories, :fat, :carb, :fiber, :protein)""", data)
        conn.commit()
    except sqlite3.IntegrityError:
        print("Food already exists")

    conn.close()


def update_food(food):
    """
    Updates food from database

    @param food: A Food object containing all food info
    @type food: Object of class Food
    """
    conn = sqlite3.connect('food.db')
    cursor = conn.cursor()
    data = {'name': food.name,
            'calories': food.calories,
            'fat': food.fat,
            'carb': food.carb,
            'fiber': food.fiber,
            'protein': food.protein}

    cursor.execute("""UPDATE food
            SET calories=:calories, fat=:fat, carb=:carb,
            fiber=:fiber, protein=:protein
            WHERE name=:name""", data)

    conn.commit()
    conn.close()


def remove_food(name):
    """
    Removes food from database

    @param name:  Name of the food
    @type  name:  text
    """
    conn = sqlite3.connect('food.db')
    cursor = conn.cursor()
    cursor.execute("DELETE from food WHERE name=:name", {'name': name})
    conn.commit()
    conn.close()
