#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "bktpool.h"
#undef STRESS_TEST
#define SHM_tid 0x123

#define SHM_busy 0x456
#define SHM_worker 0x789
#define SHM_id 0x1111
#define SHM_tid_tid 0x2222

#define SHM_SIZE 0x200

#ifndef WORK_THREAD
int *wrkid_tid;
int *wrkid_busy;
struct bkworker_t *worker;
#endif
int func(void *arg)
{
  int id = *((int *)arg);

  printf("Task func - Hello from %d\n", id);
  fflush(stdout);

  return 0;
}

int main(int argc, char *argv[])
{
#ifndef WORK_THREAD
  int shmid_id = shmget(SHM_id, SHM_SIZE, 0666 | IPC_CREAT);
  int *id = (int *)shmat(shmid_id, (void *)0, 0);
  int shmid_tid_tid = shmget(SHM_tid_tid, SHM_SIZE, 0666 | IPC_CREAT);
  int *tid = (int *)shmat(shmid_tid_tid, (void *)0, 0);
#else
  int tid[15];
  int id[15];

#endif
  int wid[15];
  int ret;

#ifndef WORK_THREAD
  int shmid_tid = shmget(SHM_tid, SHM_SIZE, 0666 | IPC_CREAT);
  wrkid_tid = (int *)shmat(shmid_tid, (void *)0, 0);
  int shmid_busy = shmget(SHM_busy, SHM_SIZE, 0666 | IPC_CREAT);
  wrkid_busy = (int *)shmat(shmid_busy, (void *)0, 0);
  int shmid_worker = shmget(SHM_worker, SHM_SIZE, 0666 | IPC_CREAT);
  worker = (struct bkworker_t *)shmat(shmid_worker, (void *)0, 0);
  for (int i = 0; i < 10; i++)
  {
    wrkid_tid[i] = 0;
    wrkid_busy[i] = 0;
  }
#else
  int shmid_tid = 0;
  int shmid_busy = 0;
  int shmid_worker = 0;
  int shmid_id = 0;
  int shmid_tid_tid = 0;
#endif
  taskid_seed = 0;
  wrkid_cur = 0;
  bktask_sz = 0;
  ret = bktpool_init(shmid_tid, shmid_busy, shmid_worker, shmid_id, shmid_tid_tid);
  if (ret != 0)
    return -1;

  id[0] = 1;
  bktask_init(&tid[0], &func, (void *)&id[0]);
  id[1] = 2;
  bktask_init(&tid[1], &func, (void *)&id[1]);
  id[2] = 5;
  bktask_init(&tid[2], &func, (void *)&id[2]);

  wid[1] = bkwrk_get_worker();
  ret = bktask_assign_worker(tid[0], wid[1]);
  if (ret != 0)
    printf("assign_task_failed tid=%d wid=%d\n", tid[0], wid[1]);

  bkwrk_dispatch_worker(wid[1]); // execute concurrently, program start execute next instruction
  sleep(1);

  wid[0] = bkwrk_get_worker();
  ret = bktask_assign_worker(tid[1], wid[0]);
  if (ret != 0)
    printf("assign_task_failed tid=%d wid=%d\n", tid[1], wid[0]);

  wid[2] = bkwrk_get_worker();
  ret = bktask_assign_worker(tid[2], wid[2]);
  if (ret != 0)
    printf("assign_task_failed tid=%d wid=%d\n", tid[2], wid[2]);

  bkwrk_dispatch_worker(wid[0]);
  bkwrk_dispatch_worker(wid[2]);

  fflush(stdout);
  sleep(1);

#ifdef STRESS_TEST
  int i = 0;
  for (i = 0; i < 15; i++)
  {
    id[i] = i;
    bktask_init(&tid[i], &func, (void *)&id[i]);

    wid[i] = bkwrk_get_worker();
    ret = bktask_assign_worker(tid[i], wid[i]);

    if (ret != 0)
      printf("assign_task_failed tid=%d wid=%d\n", tid[i], wid[i]);

    bkwrk_dispatch_worker(wid[i]);
  }

  sleep(3);
#endif

  return 0;
}