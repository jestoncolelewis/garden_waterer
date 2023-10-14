# For the garden waterer database
import funcs

db_name = "garden_waterer"

# connect to the server
oconnect = funcs.create_connection_nodb("192.168.1.188", "jeston", "")

create_database = f"""CREATE DATABASE IF NOT EXISTS {db_name};"""

# create the database
funcs.create_database(oconnect, create_database)

# reconnect
connection = funcs.create_connection("192.168.1.188", "jeston", "", db_name)

# create tables for plant data
plant_data_table = f"""
CREATE TABLE IF NOT EXISTS jade(
  id SERIAL PRIMARY KEY,
  datetime DATETIME NOT NULL,
  moisture INTEGER
);"""
funcs.execute_query(connection, plant_data_table)

# send request to arduino for data
# receive data from arduino
# store data in database
plant_data = """
INSERT INTO
  jade (datetime, moisture)
VALUES
  ();
"""

# retrieve moisture data
moisture_select = """SELECT moisture FROM jade;"""
moistures = funcs.execute_read_query(connection, moisture_select)

for moisture in moistures: # type: ignore
    print(moisture)
    # if moisture level is below dryness level
      # send command to arduino to water
    # else
      # standby
