#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define PORT "/dev/ttyUSB"

int open_port (void) {
    int fd;

    fd = open (PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror ("open_port: Unable to open port /dev/ttyUSB");
    } else {
        fcntl (fd, F_SETFL, 0);
    }

    return (fd);
}
