#include "plant.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_interface_attribs(int fd, int speed, int parity) {
    struct termios tty;

    if (tcgetattr(fd, &tty) != 0) {
        printf("error %d from tcgetattr", errno);
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag, & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 5;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        printf("error %d from tcsetattr", errno);
        return -1;
    }

    return 0;
}

void set_blocking (int fd, int should_block) {
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0) {
        printf("error %d from tggetattr", errno);
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
        printf("error %d setting term attributes", errno);
}


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