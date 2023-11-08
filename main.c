#include "plant.h"
#include "serial_tool.h"


int main(void) {
    int fd = open_port();

    ssize_t n = write(fd, "ATZ\r", 4);
    if (n < 0)
        fputs("write() of 4 bytes failed", stderr);

    close(fd);

    return 0;
}