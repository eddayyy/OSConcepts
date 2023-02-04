#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
    
    pid_t pid = fork();
    pid_t mypid  = -1;

    if(pid < 0)
    {
        perror("fork");
        exit(-1);
    }
    if(pid > 0)
    {
        mypid = getpid();
            
        if(kill(mypid, SIGSTOP) < 0)
        {
            perror("kill");
            exit(-1);
        }
        //sleep(1000);
    }
    
}