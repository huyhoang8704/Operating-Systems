#include "bktpool.h"

int bktpool_init(int shmid_tid, int shmid_busy, int shmid_worker, int shmid_id, int shmid_tid_tid)
{
   return bkwrk_create_worker(shmid_tid, shmid_busy, shmid_worker, shmid_id, shmid_tid_tid);
}
