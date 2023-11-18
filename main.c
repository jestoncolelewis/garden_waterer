#include <mariadb/mysql.h>
#include "plant.h"
#include "serial_tool.h"

#define SERIAL "/dev/ttyUSB"
#define PORT 0
#define HOST "192.168.1.188"
#define USER "jeston"
#define PASS ""
#define DB "garden_waterer"

int main(void) {
    Plant jade;
    jade.name = "jade";
    jade.moistureLevel = 0;
    jade.drynessLimit = 480;

    // connect to server
    MYSQL * mysql;
    mysql_init(mysql);
    mysql_real_connect(mysql,HOST,USER,PASS,NULL,PORT,NULL,0);

    // create database
    char* db_creation_statement = "CREATE DATABASE IF NOT EXISTS garden_waterer;";

    mysql_real_query(mysql, db_creation_statement, strlen(db_creation_statement));

    // reconnect to server
    mysql_real_connect(mysql,HOST,USER,PASS,DB,PORT,NULL,0);

    // create tables for plant data
    char* tbl_creation_statement = "CREATE TABLE IF NOT EXISTS jade("
                                      "id, SERIAL PRIMARY KEY,"
                                      "datetime DATETIME NOT NULL,"
                                      "moisture INTEGER);";
    mysql_real_query(mysql,tbl_creation_statement,strlen(tbl_creation_statement));

    // open serial between arduino
    int fd;
    fd = open_port(SERIAL);

    configure_port(fd);

    ssize_t n = write(fd,"ATZ\r",4);
    if (n < 0)
        fputs("write() of 4 bytes failed",stderr);

    long moisture;
    moisture = read(fd,"AR\r",2); // update second argument

    jade.moistureLevel = moisture;

    // store data in database
    MYSQL_STMT * insert;
    insert = mysql_stmt_init(mysql);
    char* store_plant_data = "INSERT INTO"
                             "jade(datetime, moisture)"
                             "VALUES"
                             "(NOW(), " /*jade.moistureLevel*/;
    mysql_stmt_prepare(insert,store_plant_data,strlen(store_plant_data));
    mysql_stmt_execute(insert);
    mysql_stmt_close(insert);

    // retrieve moisture data
    MYSQL_STMT * select;
    char * moisture_select = "SELECT moisture FROM jade";
    select = mysql_stmt_init(mysql);
    mysql_stmt_prepare(select,moisture_select,strlen(moisture_select));
    mysql_stmt_execute(select);
    mysql_stmt_close(select);

    bool water = waterIfNeeded(jade);

    if (water == true) {
        write(fd,"true\r",5);
    }

    close(fd);

    return 0;
}