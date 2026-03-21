#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

int main(int argc, char *argv[])
{
    int fd;
    int ret;
    char buf1[32] = {0};
    char buf2[32] = "nihao!";
    struct pollfd fds[1];

    fd = open("/dev/test", O_RDWR);  // 打开设备节点
    if (fd < 0)
    {
        perror("open error \n");
        return fd;
    }

    fds[0].fd = fd;
    fds[0].events = POLLIN;
    printf("read before\n");

    while(1){
        ret = poll (fds, 1, 3000);
        if(!ret){
            printf("timeout \n");
        }else if(fds[0].revents == POLLIN){
            read(fd, buf1, 32);
            printf("buf is %s\n", buf1);
            sleep(1);
        }
    }

    printf("read after\n");

    close(fd);
    return 0;
}