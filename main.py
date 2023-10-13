import funcs

db_name = "test"

oconnect = funcs.create_connection_nodb("localhost", "mysql", "")

create_database = f"""CREATE DATABASE IF NOT EXISTS {db_name}"""

funcs.create_database(oconnect, create_database)

create_users_table = """
CREATE TABLE IF NOT EXISTS users (
  id SERIAL PRIMARY KEY,
  name VARCHAR(50) NOT NULL,
  age INTEGER,
  gender VARCHAR(6),
  nationality VARCHAR(200)
);
"""

connection = funcs.create_connection("localhost", "mysql", "", db_name)

# create the table
funcs.execute_query(connection, create_users_table)

create_users = """
INSERT INTO
  users (name, age, gender, nationality)
VALUES
  ('James', 25, 'male', 'USA'),
  ('Leila', 32, 'female', 'France'),
  ('Brigitte', 35, 'female', 'England'),
  ('Mike', 40, 'male', 'Denmark'),
  ('Elizabeth', 21, 'female', 'Canada');
"""
# add users
funcs.execute_query(connection, create_users)

select_users = "SELECT * FROM users"
users = funcs.execute_read_query(connection, select_users)

for user in users: # type: ignore
    print(user)


# For the garden waterer database
# connect to the server
# create the database
# create tables for plant data
# send request to arduino for data
# receive data from arduino
# store data in database
# retrieve moisture data
# if moisture level is below dryness level
  # send command to arduino to water
# else
  # standby