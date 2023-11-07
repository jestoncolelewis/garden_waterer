#include "plant.h"
#include "serial_tool.h"


int main(void) {
    char *portname = "/dev/ttyUSB1";
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);

    Plant jade;
    jade.name = "Jade";
    jade.drynessLimit = 480;

    if (fd < 0) {
        printf("error %d opening %s: %s", errno, portname, strerror (errno));
        return -1;
    }

    set_interface_attribs (fd, B115200, 0);
    set_blocking (fd, 0);

    write(fd, "hello!\n", 7);

    usleep((7 + 25) * 100);
    char buf [100];
    int n = read(fd, buf, sizeof buf);

    jade.moistureLevel = n;

    return 0;
}