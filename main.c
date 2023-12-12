#include "plant.h"
#include "serial_tool.h"
#include "sql_tool.h"

#define SERIAL "/dev/ttyACM0/"
#define PORT 3306
#define HOST "192.168.1.188"
#define DB "garden_waterer"

int main(int argc, char* argv[]) {
    Plant jade;
    jade.name = "jade";
    jade.moistureLevel = 500;
    jade.drynessLimit = 480;

    MYSQL mysql = db_setup(HOST,argv[1],argv[2],DB,PORT);

    // open serial between arduino
    /* int fd;
    fd = open_port(SERIAL);

    configure_port(fd);

    ssize_t n = write(fd,"ATZ\r",4);
    if (n < 0)
        fputs("write() of 4 bytes failed",stderr);

    long data_moisture;
    data_moisture = read(fd,"AR\r",2); // update second argument

    jade.moistureLevel = data_moisture;*/

    process(jade, &mysql);

    /* bool water = waterIfNeeded(jade);

    if (water == true) {
        write(fd,"true\r",5);
    }

    close(fd); */

    mysql_close(NULL);
    return 0;
}