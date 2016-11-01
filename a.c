#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void func(int a)
{
    if(1)
    {
        while(a<100)
        {
            a++;
        }
        func(a);
    }
    return 0;
}

int main()
{
    pid_t pid;
    while(1)
    {
        pid=fork();
        func(1);
    }

    return 0;
}
