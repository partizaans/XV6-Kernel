#include "types.h"
#include "stat.h"
#include "user.h"

#define LOTTERY 0
#define NCHILD 5
#define PRIORITY 2
#define SJF 1

void delay(int numberOfClocks)
{
    int firstClock = uptime();
    int incClock = uptime();
    while (incClock >= (firstClock + numberOfClocks))
    {
        incClock = uptime();
    }
}

int main(void){
    int pid = getpid();
    int queue = LOTTERY;
    int i;
    for (i = 0; i < 3 * NCHILD; i++)
    {
        if (pid > 0)
        {
            pid = fork();
            if (pid > 0)
            {
                if (i < NCHILD)
                {
                    setQueue(PRIORITY);
                    setPriority(NCHILD*3-i);
                }
                else if (i < NCHILD * 2)
                {
                    setQueue(SJF);
                    setBurstTime(NCHILD*3-i);
                }
                else if (i < NCHILD * 3)
                {
                    setQueue(LOTTERY);
                    setTicket(NCHILD*3-i);
                }
            }
            if (pid == 0)
            {
                queue = i < NCHILD ? PRIORITY : i < NCHILD * 2 ? SJF : LOTTERY;
                break;
            }
        }
    }

    if (pid < 0)
    {
        printf(2, "fork error\n");
    }
    else if (pid == 0 && (queue == LOTTERY || queue == SJF))
    {
        int i;
        for (i = 0; i < 250000; i++)
            delay(2000000000);
        printf(1, "pid %d finished\n", getpid());
        exit();
    }
    else if (pid == 0 && queue == PRIORITY)
    {
        printf(1, "IO bound process with pid %d finished\n", getpid());
        exit();
    }
    else
    {
        printInfos();
        int i;
        for (i = 0; i < NCHILD * 3; i++)
            wait();
        printf(1, "main program wirh pid %d finished\n", getpid());
        exit();
    }
}