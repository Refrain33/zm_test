#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include "make_log.h"

int fdfs_upload(char *filePath)
{
    //判断错误
    int ret=0;
    //文件描述符
    int pfd[2]={0};
    //存放文件名
    char buf[1024]={0};
    //进程id
    pid_t pid=0;
    //读取字串数
    int readCount=0;

    //创建管道
    ret=pipe(pfd);
    if(ret!=0)
    { 
        printf("func pipe is err:%d\n",ret);
        dumpmsg_to_file("./", "fdfs_upload", NULL,__LINE__, "func pipe()","func pipe err" );
        return ret;
    }

    //创建子进程
    pid=fork();
    if(pid<0)
    {
        printf("func fork is err:%d\n",ret);
        dumpmsg_to_file("./", "fdfs_upload", NULL,__LINE__, "func fork()","func fork err" );
        return ret;
    }

    //父进程
    if(pid>0)
    {
        close(pfd[1]);
        
        while((readCount=read(pfd[0],buf,sizeof(buf)))>0)
        {
            buf[readCount]='\0';
        }
        
        wait(NULL);
        printf("---------------SUCCESS-------------\n");
        printf("new file path:%s\n",buf);
        close(pfd[0]);
    }
    //子进程
    else if(pid==0)
    {
        close(pfd[0]);
        //重定向文件描述符
        ret=dup2(pfd[1],STDOUT_FILENO);
        if(ret==-1)
        {
            printf("%d func dup2 err:%d\n",__LINE__,ret);
            dumpmsg_to_file("./", "test_main", NULL,__LINE__, "func dup2()","func dup2 err" );
            return ret;
        }
        //执行上传操作
        ret=execl("/home/itcast/project2/fastdfs-5.05/client/fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf",filePath,NULL);
        if(ret!=0)
        {
            printf("func execl err:%d\n",ret);
            dumpmsg_to_file("./", "test_main", NULL,__LINE__, "func execl()","func execl err" );
            return ret;
        }
        close(pfd[1]);
    }

    return ret;
}
