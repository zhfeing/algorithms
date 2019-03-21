#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sem.h>
int signal = 0;
char buffer[1000];
void *function(void *args);
int main()
{
    pthread_t a_thread;
    int res;
    res = pthread_create(&a_thread, NULL, function, NULL);
    if(res != NULL)
    {
        printf("create thread function failed");
        exit(-1);
    }
    while(1)
    {
        fflush(stdout);
        if(signal)
        {
            printf("%s\nnext line\n", buffer);
            signal = 0;
        }
    }
    return 0;
}
void* function(void* args)
{
    while(1)
    {
        if(scanf("%s", buffer))
            signal = 1;
    }
}
