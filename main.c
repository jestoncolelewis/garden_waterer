#include "plant.h"
#include "serial_tool.h"
#include "sql_tool.h"

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

    db_setup(HOST,USER,PASS,DB,PORT);

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

    process(jade);

    bool water = waterIfNeeded(jade);

    if (water == true) {
        write(fd,"true\r",5);
    }

    close(fd);
    mysql_library_end();

    return 0;
}