import funcs
import os
import serial
import time

# For the garden waterer database
db_name = "garden_waterer"
plant_name = "jade"

# connect to the server
oconnect = funcs.create_connection_nodb("192.168.1.188", "jeston", os.getenv("MARIA_DB_PASS"))

create_database = f"""CREATE DATABASE IF NOT EXISTS {db_name};"""

# create the database
funcs.create_database(oconnect, create_database)

# reconnect
connection = funcs.create_connection("192.168.1.188", "jeston", os.getenv("MARIA_DB_PASS"), db_name)

# create tables for plant data
plant_data_table = f"""
CREATE TABLE IF NOT EXISTS {plant_name}(
  id SERIAL PRIMARY KEY,
  datetime DATETIME NOT NULL,
  moisture INTEGER
);"""
funcs.execute_query(connection, plant_data_table)

moisture_level = 0
arduino = serial.Serial(
    port="/dev/cu.usbmodem101",
    baudrate=115200,
    # timeout=.1
)
time.sleep(1)
arduino.reset_input_buffer()
arduino.reset_output_buffer()
if arduino.is_open:
    print("Getting moisture level")
    arduino.write("true".encode("utf-8"))
    data = arduino.readline()
    if data:
        moisture_level = int(data)

# store data in database
plant_data = f"""
INSERT INTO
  {plant_name} (datetime, moisture)
VALUES
  (NOW(),{moisture_level});
"""
funcs.execute_query(connection, plant_data)
print("Stored moisture data")

# retrieve moisture data
moisture_select = f"""SELECT moisture FROM {plant_name};"""
moistures = funcs.execute_read_query(connection, moisture_select)

for moisture in moistures: # type: ignore
    print(moisture)
    # if moisture level is below dryness level
      # send command to arduino to water
    # else
      # standby
