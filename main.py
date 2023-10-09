import funcs

connection = funcs.create_connection("localhost", "mysql", "", "test")

create_users_table = """
CREATE TABLE IF NOT EXISTS users (
  id SERIAL PRIMARY KEY,
  name VARCHAR(50) NOT NULL,
  age INTEGER,
  gender VARCHAR(6),
  nationality VARCHAR(200)
);
"""

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