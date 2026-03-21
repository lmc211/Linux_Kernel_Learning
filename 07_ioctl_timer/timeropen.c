#include "timerlib.h"

int timeropen(int fd){
    int ret;
    ret = ioctl(fd, TIME_OPEN_CMD);
    if(ret < 0){
        printf("timeropen error \n");
        exit(-1);
    }
}