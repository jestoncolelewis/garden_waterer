#include <mariadb/mysql.h>

void db_setup(char* host, char* user, char* pass, char* db, char* port) {
    // connect to server
    mysql_library_init(0, NULL, NULL);
    MYSQL * mysql;
    mysql_init(mysql);
    mysql_real_connect(mysql,host,user,pass,NULL,port,NULL,0);

    // create database
    char* db_creation_statement = "CREATE DATABASE IF NOT EXISTS garden_waterer;";

    mysql_real_query(mysql, db_creation_statement, strlen(db_creation_statement));

    // reconnect to server
    mysql_real_connect(mysql,host,user,pass,db,port,NULL,0);

    // create tables for plant data
    char* tbl_creation_statement = "CREATE TABLE IF NOT EXISTS jade("
                                   "id, SERIAL PRIMARY KEY,"
                                   "datetime DATETIME NOT NULL,"
                                   "moisture INTEGER);";
    mysql_real_query(mysql,tbl_creation_statement,strlen(tbl_creation_statement));
}

void process(Plant plant) {
    enum insert_params {
        moisture,
        par_count
    };

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
    insert_bind [moisture].buffer = (long *) & plant.moistureLevel;
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
}