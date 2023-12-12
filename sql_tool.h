#include <mariadb/mysql.h>

#define CREATE_TABLE "CREATE TABLE IF NOT EXISTS jade(id SERIAL PRIMARY KEY, timestamp TIMESTAMP, moisture INTEGER);"

#define INSERT "INSERT INTO jade(moisture) VALUES(?)"

#define SELECT "SELECT moisture FROM jade"


MYSQL db_setup(char* host, char* user, char* pass, char* db, int port) {
    // connect to server
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    if(!mysql_real_connect(mysql,host,user,pass,db,port,NULL,0)) {
        fprintf(stderr, "Error while connecting: %s\n", mysql_error(mysql));
        exit(0);
    }

    // create tables for plant data
    if(mysql_query(mysql,CREATE_TABLE)) {
        fprintf(stderr, "Error while creating table: %s\n", mysql_error(mysql));
        exit(0);
    }

    return *mysql;
}

void process(Plant plant, MYSQL *mysql) {
    // store data in database
    MYSQL_STMT * insert;
    MYSQL_BIND insert_bind[1];
    int param_count;
    int moisture;

    insert = mysql_stmt_init(mysql);

    if(mysql_stmt_prepare(insert,INSERT,strlen(INSERT))) {
        fprintf(stderr, "Error while creating prepared statement: %s\n", mysql_stmt_error(insert));
        exit(0);
    }

    param_count = mysql_stmt_param_count(insert);
    if(param_count != 1) {
        fprintf(stderr, " invalid parameter count returned by MYSQL\n");
        exit(0);
    }

    memset(insert_bind, 0, sizeof(insert_bind));

    insert_bind[0].buffer_type = MYSQL_TYPE_LONG;
    insert_bind[0].buffer = (char *)&moisture;
    insert_bind[0].is_null = 0;
    insert_bind[0].length = 0;

    if(mysql_stmt_bind_param(insert,insert_bind)) {
        fprintf(stderr, "Error while creating bound values: %s\n", mysql_stmt_error(insert));
        exit(0);
    }

    moisture = plant.moistureLevel;

    if(mysql_stmt_execute(insert)) {
        fprintf(stderr, "Error while executing statement: %s\n", mysql_stmt_error(insert));
        exit(0);
    }
    mysql_stmt_close(insert);

    // retrieve moisture data TODO
    /* MYSQL_STMT * select;
    select = mysql_stmt_init(mysql);
    mysql_stmt_prepare(select,SELECT,strlen(SELECT));
    mysql_stmt_execute(select);
    mysql_stmt_close(select); */
}