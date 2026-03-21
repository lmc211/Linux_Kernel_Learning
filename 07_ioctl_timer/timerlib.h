#ifndef TIMERLIB_H
#define TIMERLIB_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define TIME_OPEN_CMD _IO('L',0)
#define TIME_CLOSE_CMD _IO('L',1)
#define TIME_SETTING_CMD _IOW('L',2,int)


int devopen();
int timeropen(int fd);
int timerclose(int fd);
int timerset(int fd, int arg);

#endif