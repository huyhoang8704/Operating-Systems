#ifndef BKTPOOL_H
#define BKTPOOL_H

#include <stdlib.h>

#include <pthread.h>

#define MAX_WORKER 10
#define WRK_THREAD 1
#define STACK_SIZE 4096
#define SIG_DISPATCH SIGUSR1
// #define WORK_THREAD

#ifdef WORK_THREAD
/* Task ID is unique non-decreasing integer */
int* taskid_seed;

int wrkid_tid[MAX_WORKER];
int wrkid_busy[MAX_WORKER];
int* wrkid_cur;

// Linked List
struct bktask_t {
  void( * func)(void * arg);
  void * arg;
  unsigned int bktaskid;
  struct bktask_t * tnext;
};

struct bktask_t* bktask;

int* bktask_sz;

// Worker is bind with bktask
struct bkworker_t {
  void( * func)(void * arg);
  void * arg;
  unsigned int wrkid;
  unsigned int bktaskid;
};

// MAX_WORKER numbers of worker
struct bkworker_t worker[MAX_WORKER];

#else
// Using IPC
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;

int* taskid_seed;
int* wrkid_tid;
int* wrkid_busy;
int* wrkid_cur;

// Linked List
struct bktask_t {
  void( * func)(void * arg);
  void * arg;
  unsigned int bktaskid;
  struct bktask_t * tnext;
};

struct bktask_t * bktask;

int* bktask_sz;

// Worker is bind with bktask
struct bkworker_t {
  void( * func)(void * arg);
  void * arg;
  unsigned int wrkid;
  unsigned int bktaskid;
};
struct bkworker_t * worker;

#define SHARED_MEMORY_QUANTITY 1024
int* sharedMemory[SHARED_MEMORY_QUANTITY];
#define MAX_SHM_SIZE 4096
int* tmpShared;

#endif

/* Prototype API */

/* bktpool module */
int bktpool_init();

/* bktask module */
struct bktask_t * bktask_get_byid(unsigned int bktaskid);
int bktask_init(unsigned int * bktaskid, void * func, void * arg);
int bktask_assign_worker(unsigned int bktaskid, unsigned int wrkid);

/* bkwrk module */
void * bkwrk_worker(void * arg);
int bkwrk_create_worker();
int bkwrk_dispatch_worker(unsigned int wrkid);
int bkwrk_get_worker();

#endif