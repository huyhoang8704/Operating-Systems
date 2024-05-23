#include "bktpool.h"

int bktpool_init()
{
   #ifdef WORK_THREAD
   taskid_seed = malloc(sizeof(int));
   wrkid_cur = malloc(sizeof(int));
   bktask_sz = malloc(sizeof(int));
   #else
   shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
   taskid_seed = (int *)shmat(shmid, NULL, 0);
   shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
   wrkid_cur = (int *)shmat(shmid, NULL, 0);
   shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
   bktask_sz = (int *)shmat(shmid, NULL, 0);
   shmid = shmget(IPC_PRIVATE, sizeof(int) * MAX_WORKER, IPC_CREAT | 0666);
   wrkid_tid = (int *)shmat(shmid, NULL, 0);
   shmid = shmget(IPC_PRIVATE, sizeof(int) * MAX_WORKER, IPC_CREAT | 0666);
   wrkid_busy = (int *)shmat(shmid, NULL, 0);
   shmid = shmget(IPC_PRIVATE, sizeof(struct bkworker_t) * MAX_WORKER, IPC_CREAT | 0666);
   worker = (struct bkworker_t *)shmat(shmid, NULL, 0);
   for (int i = 0; i < SHARED_MEMORY_QUANTITY; i++)
   {
      shmid = shmget(IPC_PRIVATE, (unsigned long)MAX_SHM_SIZE, IPC_CREAT | 0666);
      sharedMemory[i] = (int *)shmat(shmid, NULL, 0);
   }
   #endif
   return bkwrk_create_worker();
} 
