#ifndef BKTPOOL_H
#define BKTPOOL_H
// #define DEBUG
#include <stdlib.h>

#include <pthread.h>

#define MAX_WORKER 10
#define WRK_THREAD 1
#define STACK_SIZE 4096
#define SIG_DISPATCH SIGUSR1

#define WORK_THREAD

/* Task ID is unique non-decreasing integer */
int taskid_seed;

int wrkid_cur;
struct bktask_t
{
  void (*func)(void *arg);
  void *arg;
  unsigned int bktaskid;
  struct bktask_t *tnext;
} *bktask;

int bktask_sz;

struct bkworker_t
{
  void (*func)(void *arg);
  void *arg;
  unsigned int wrkid;
  unsigned int bktaskid;
};
#ifdef WORK_THREAD
int wrkid_tid[MAX_WORKER];
int wrkid_busy[MAX_WORKER];
struct bkworker_t worker[MAX_WORKER];
#endif

/* Prototype API */

/* bktpool module */

int bktpool_init(int, int, int, int, int);

/* bktask module */
struct bktask_t *bktask_get_byid(unsigned int bktaskid);
int bktask_init(unsigned int *bktaskid, void *func, void *arg);
int bktask_assign_worker(unsigned int bktaskid, unsigned int wrkid);

/* bkwrk module */
void *bkwrk_worker(void *arg);
int bkwrk_create_worker(int, int, int, int, int);
int bkwrk_dispatch_worker(unsigned int wrkid);
int bkwrk_get_worker();

#endif