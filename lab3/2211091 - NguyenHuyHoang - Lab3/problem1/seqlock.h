#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock { /* TODO: implement the structure */
   pthread_mutex_t lock;
   int count;
} pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_init(&rw->lock, NULL);
   rw->count = 0;
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_lock(&rw->lock);
   rw->count += 1;
}

static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   rw->count += 1;
   pthread_mutex_unlock(&rw->lock);

}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   if (rw->count % 2 != 0)
   {
      pthread_mutex_lock(&rw->lock);
      if (rw->count % 2 == 0)
      {
         return 1;
      }
   }
   return 1;
}


static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_unlock(&rw->lock);
   return 0;
}

