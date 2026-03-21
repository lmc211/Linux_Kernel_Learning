#include "timerlib.h"

int timerclose(int fd){
    int ret;
    ret = ioctl(fd, TIME_CLOSE_CMD);
    if(ret < 0){
        printf("timerclose error \n");
        exit(-2);
    }
}