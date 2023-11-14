#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int open_port (char* port) {
    int fd;

    fd = open (port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror ("open_port: Unable to open port /dev/ttyUSB"); // update port name
    } else {
        fcntl (fd, F_SETFL, 0);
    }

    return (fd);
}

void configure_port(int fd) {
    struct termios options;

    tcgetattr(fd, &options);

    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag |= (CLOCAL | CREAD);

    tcsetattr(fd, TCSADRAIN, &options);
}
