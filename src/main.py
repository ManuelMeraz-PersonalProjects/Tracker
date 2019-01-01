import sqlite3
from Food import Food, Macronutrients, Serving


def create_food_table(conn, cursor):
    with conn:
        cursor.execute("""CREATE TABLE food (
                        name text,
                        calories real,
                        fat real,
                        carb real,
                        fiber real,
                        protein real
                        )""")


def get_food(name, cursor):
    """ returns all results with that name """
    cursor.execute("SELECT * FROM food WHERE name=:name", {'name': name})
    return cursor.fetchall()


def food_exists(name, cursor):
    foods = get_food(name,  cursor)
    for food in foods:
        if food[0] == name:
            return True

    return False


def insert_food(food, conn, cursor):
    """ inserts food into the database """
    if not food_exists(food.name, cursor):
        with conn:
            data = {'name': food.name,
                    'calories': food.calories,
                    'fat': food.fat,
                    'carb': food.carb,
                    'fiber': food.fiber,
                    'protein': food.protein}

            cursor.execute("""INSERT INTO food VALUES (
                 :name, :calories, :fat, :carb, :fiber, :protein)""", data)
    else:
        print("Food exists already")


def update_food(food, conn, cursor):
    """ updates food from database """
    with conn:
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


def remove_food(name, conn, cursor):
    with conn:
        cursor.execute("DELETE from food WHERE name=:name", {'name': name})


if __name__ == '__main__':
    serving = Serving('g', 100)
    macros = Macronutrients(17, 1, 1, 0, 1)
    food = Food("sweet potato", macros, serving)

    conn = sqlite3.connect(':memory:')
    c = conn.cursor()

    create_food_table(conn, c)

    insert_food(food, conn, c)
    d_food = get_food("sweet potato", c)
    print(d_food)

    food.calories = 18
    update_food(food, conn, c)
    d_food = get_food("sweet potato", c)
    print(d_food)

    remove_food("sweet potato", conn, c)
    d_food = get_food("sweet potato", c)
    print(d_food)

    conn.close()
