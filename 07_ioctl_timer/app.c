#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "timerlib.h"

int main(int argc,char *argv[])
{
    int fd;
    fd = devopen("/dev/test");

    timerset(fd, 1000);
    timeropen(fd);
    sleep(3);
    timerset(fd, 3000);
    sleep(7);
    timerclose(fd);

    close(fd);
    return 0;
}