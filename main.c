#include "plant.h"
#include "serial_tool.h"

#define PORT "/dev/ttyUSB"

int main(void) {
    int fd = open_port(PORT);
    Plant jade;

    configure_port(fd);

    ssize_t n = write(fd, "ATZ\r", 4);
    if (n < 0)
        fputs("write() of 4 bytes failed", stderr);

    long moisture = read(fd, "AR\r", 2); // update second argument

    jade.moistureLevel = moisture;

    waterIfNeeded(jade);

    close(fd);

    return 0;
}