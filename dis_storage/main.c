#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include "fdfs_func.h"
#include "make_log.h"

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("sorry,you should input 2 pragma\n");
        return -1;
    }
    //判断错误
    int ret=0;

    ret=fdfs_upload(argv[1]);
    if(ret!=0)
    {
        printf("func fdfs_upload err:%d\n",ret);
        ret=dumpmsg_to_file("./", "test_main",NULL,__LINE__, "fdfs_upload","fdfs_upload err");
        return ret;
    }

    return 0;
}
