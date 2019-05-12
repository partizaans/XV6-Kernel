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
    int arg = 101;
    void *arg_ptr = &arg;
    thread_create();
    thread_create();
    thread_create();
    int tid1, tid2,tid3;
    thread_associate(&tid1, thread_1, arg_ptr);
    thread_associate(&tid2, thread_2, arg_ptr);
    thread_associate(&tid3, thread_3, arg_ptr);
    printf(1, "tid1: %d\t", tid1);
    printf(1, "tid2: %d\t", tid2);
    printf(1, "tid3: %d\n", tid3);
    thread_join();
    thread_join();
    thread_join();
    exit();
}
