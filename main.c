#include "plant.h"
#include "serial_tool.h"
#include "sql_tool.h"

#define PORT "/dev/ttyUSB"
#define HOST "192.168.1.188"
#define USER "jeston"
#define PASS ""

int main(void) {
    Plant jade;
    jade.name = "jade";
    jade.moistureLevel = 0;
    jade.drynessLimit = 480;

    char *db_name;
    db_name = "garden_waterer";

    // connect to server
    int o_connect;
    o_connect = create_connect_nodb(HOST,USER,PASS);

    // create database
    char *db_creation_statement;
    db_creation_statement = "CREATE DATABASE IF NOTE EXISTS %c", db_name;

    create_database(o_connect, db_creation_statement);

    // reconnect to server
    int connection;
    connection = create_connect(HOST,USER,PASS);

    // create tables for plant data
    char *tbl_creation_statement;
    tbl_creation_statement = "CREATE TABLE IF NOT EXISTS %c("
                             "id, SERIAL PRIMARY KEY,"
                             "datetime DATETIME NOT NULL,"
                             "moisture INTEGER);", jade.name;
    execute_query(connection, tbl_creation_statement);

    // open serial between arduino
    int fd;
    fd = open_port(PORT);

    configure_port(fd);

    ssize_t n = write(fd, "ATZ\r", 4);
    if (n < 0)
        fputs("write() of 4 bytes failed", stderr);

    long moisture;
    moisture = read(fd, "AR\r", 2); // update second argument

    jade.moistureLevel = moisture;

    // store data in database
    char* store_plant_data;
    store_plant_data = "INSERT INTO"
                       "    %c (datetime, moisture)"
                       "VALUES"
                       "    (NOW(), %l", jade.name, jade.moistureLevel;
    execute_query(connection, store_plant_data);

    // retrieve moisture data
    char* moisture_select;
    moisture_select = "SELECT moisture FROM %c", jade.name;
    execute_read_query(connection, moisture_select);

    bool water = waterIfNeeded(jade);

    if (water == true) {
        write(fd, "true\r", 5);
    }

    close(fd);

    return 0;
}