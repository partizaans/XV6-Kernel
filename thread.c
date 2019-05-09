#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"


#define THREAD_POOL_SIZE 5
#define PAGE_SIZE 4096

struct {
    int is_locked;
    void *stack;
} threads[THREAD_POOL_SIZE];

void thread_pool_init() {
    for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
        void *stack = malloc(PAGE_SIZE * 2);
        if (!stack) {
            printf(1, "Error: malloc failed\n");
            exit();
        }
        if ((uint) stack % PAGE_SIZE)
            stack = stack + (4096 - (uint) stack % PAGE_SIZE);
        threads[i].stack = stack;
        threads[i].is_locked = 0;
    }
}

int thread_create(void (*start_routine)(void *), void *arg) {
    for (int i = 0; i < THREAD_POOL_SIZE; ++i)
        if (!threads[i].is_locked)
            return clone(start_routine, arg, threads[i].stack);
    return 2;
//    printf("No free thread in pool\n");
}

