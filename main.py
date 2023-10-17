import funcs
import os
import serial

ser = serial.Serial(
    port="/dev/cu.usbmodem101",
    baudrate=9600,
)

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
if ser.isOpen(): # type: ignore
    # send request to arduino for data
    t = 't'.encode().hex()
    ser.write(bytes(t, "utf-8"))
    ser.close()

    # receive data from arduino
    ser.open()
    s = ser.readline()
    val = s.decode()
    moisture_level = int(val)
    ser.close()

# store data in database
plant_data = f"""
INSERT INTO
  {plant_name} (datetime, moisture)
VALUES
  (NOW(),{moisture_level});
"""
funcs.execute_query(connection, plant_data)

# retrieve moisture data
moisture_select = f"""SELECT moisture FROM {plant_name};"""
moistures = funcs.execute_read_query(connection, moisture_select)

for moisture in moistures: # type: ignore
    print(moisture)
    # if moisture level is below dryness level
      # send command to arduino to water
    # else
      # standby

ser.close()