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
    redisContext *redis_conn = NULL;
    int ret=0;
    char strVal[100]={0};

    redis_conn=rop_connectdb_nopwd("127.0.0.1","6379");
    if(redis_conn == NULL)
    {
        LOG(REDIS_TEST_MODULE,REDIS_TEST_PROC,"conn error");
        exit(1);
    }

    ret=rop_set_string(redis_conn,"aixi","lol");
    if(ret == -1)
    {
        LOG(REDIS_TEST_MODULE,REDIS_TEST_PROC,"set %s %s error","aixi","lol");
        exit(1);
    }

    ret=rop_get_string(redis_conn,"aixi",strVal);
    if(ret == -1)
    {
        printf("!!!!!");
        LOG(REDIS_TEST_MODULE,REDIS_TEST_PROC,"get strVal error");
        exit(1);
    }
    printf("strVal:%s\n",strVal);

    rop_disconnect(redis_conn);

    return 0;
}
