#include "timerlib.h"

int devopen(char* dev_path){
    int fd = open(dev_path, O_RDWR);    //打开设备节点
    if(fd < 0)
    {
        perror("open error \n");
        return fd;
    }
    return fd;
}
    