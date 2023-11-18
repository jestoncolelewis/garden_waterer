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

    enum insert_params {
        moisture,
        par_count
    };

    // connect to server
    mysql_library_init(0, NULL, NULL);
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

    long data_moisture;
    data_moisture = read(fd,"AR\r",2); // update second argument

    jade.moistureLevel = data_moisture;

    // store data in database
    MYSQL_STMT * insert;
    MYSQL_BIND insert_bind [par_count] = {0};
    insert = mysql_stmt_init(mysql);
    char* store_plant_data = "INSERT INTO"
                             "jade(datetime, moisture)"
                             "VALUES"
                             "(NOW(), " /*jade.moistureLevel*/;
    mysql_stmt_prepare(insert,store_plant_data,strlen(store_plant_data));
    insert_bind [moisture].buffer_type = MYSQL_TYPE_LONG;
    insert_bind [moisture].buffer = (long *) & data_moisture;
    mysql_stmt_bind_param(insert,insert_bind);
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
    mysql_library_end();

    return 0;
}