#include "types.h"
#include "stat.h"
#include "user.h"


void thread_1(void *arg_ptr) {
    printf(1, "Is in thread 1\n");
    exit();
}


void thread_2(void *arg_ptr) {
    printf(1, "Is in thread 2\n");
    exit();

}


void thread_3(void *arg_ptr) {
    printf(1, "Is in thread 3\n");
    exit();

}

int main() {
    int pid_1;
    int pid_2;
    int pid_3;
    int arg = 101;
    void *arg_ptr = &arg;
    pid_1 = thread_create(thread_1, arg_ptr);
    pid_2 = thread_create(thread_2, arg_ptr);
    pid_3 = thread_create(thread_3, arg_ptr);
    printf(1, "pid1: %d\t", pid_1);
    printf(1, "pid2: %d\t", pid_2);
    printf(1, "pid3: %d\n", pid_3);
    thread_join();
    thread_join();
    thread_join();
    return 0;
}
