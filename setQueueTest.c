#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    setQueue(1);
    setBurstTime(10);
    printQueue();
    exit();
}