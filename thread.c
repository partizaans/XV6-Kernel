#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"


#define THREAD_POOL_SIZE 5
#define PGSIZE (4096)

struct {
    int is_locked;
    void *stack;
} threads[THREAD_POOL_SIZE];

void thread_pool_init() {
    for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
        void *stack = malloc(PGSIZE * 2);
        if (!stack) {
            printf(1, "Error: malloc failed\n");
            exit();
        }
        if ((uint) stack % PGSIZE)
            stack = stack + (4096 - (uint) stack % PGSIZE);
        threads[i].stack = stack;
        threads[i].is_locked = 0;
    }
}

int thread_create(void (*start_routine)(void *), void *arg) {
  void *stack = malloc(PGSIZE*2);
  if (!stack) {
    printf(1, "Error: malloc failed\n");
    exit();
  }

  if((uint)stack % PGSIZE) {
    stack = stack + (4096 - (uint)stack % PGSIZE);
  }

  return clone(start_routine, arg, stack);
}


int
thread_join()
{
    void* ustack;
    int thread_id = join(&ustack);
    if (thread_id != -1) {
        free(ustack);
    }

    return thread_id;
}
