#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <hiredis.h>

#include "make_log.h"

#define REDIS_TEST_MODULE "test"
#define REDIS_TEST_PROC "redis_test"

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("sorry,you should input key and value\n");
        exit(1);
    }

    redisContext *redis_conn = NULL;
    int ret=0;
    char strVal[100]={0};

    redis_conn=rop_connectdb_nopwd("127.0.0.1","6379");
    if(redis_conn == NULL)
    {
        LOG(REDIS_TEST_MODULE,REDIS_TEST_PROC,"conn error");
        exit(1);
    }

    ret=rop_set_string(redis_conn,argv[1],argv[2]);
    if(ret == -1)
    {
        LOG(REDIS_TEST_MODULE,REDIS_TEST_PROC,"set %s %s error",argv[1],argv[2]);
        exit(1);
    }
    printf("-------------SET SUCCEED-------------\n");

    ret=rop_get_string(redis_conn,argv[1],strVal);
    if(ret == -1)
    {
        printf("!!!!!!!!!!!!!!!\n");
        LOG(REDIS_TEST_MODULE,REDIS_TEST_PROC,"get %s error",argv[1]);
        exit(1);
    }
    printf("-------------GET SUCCEED-------------\n");
    printf("strVal:%s\n",strVal);

    rop_disconnect(redis_conn);

    return 0;
}
