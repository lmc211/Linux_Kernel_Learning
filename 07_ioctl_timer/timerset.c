#include "timerlib.h"

int timerset(int fd, int arg){
    int ret;
    ret = ioctl(fd, TIME_SETTING_CMD, arg);
    if(ret < 0){
        printf("timerset error \n");
        exit(-3);
    }
}