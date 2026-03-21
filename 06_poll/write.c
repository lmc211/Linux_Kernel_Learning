#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf1[32] = {0};
    char buf2[32] = "nihao!";
    fd = open("/dev/test", O_RDWR|O_NONBLOCK);  //打开设备节点
    if(fd < 0)
    {
        perror("open error \n");
        return fd;
    }

    printf("write before\n");
    write(fd, buf2, strlen(buf2));
    printf("write after\n");

    close(fd);
    return 0;
}