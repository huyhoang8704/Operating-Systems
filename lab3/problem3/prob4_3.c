#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#define MAX_LOG_LENGTH 10
#define MAX_BUFFER_SLOT 6
#define MAX_LOOPS 30

char logbuf[MAX_BUFFER_SLOT][MAX_LOG_LENGTH];
sem_t empty;
pthread_mutex_t lock;
int count;
void flushlog();

struct _args
{
  unsigned int interval;
};

void *wrlog(void *data)
{
  char str[MAX_LOG_LENGTH];
  int id = *(int *)data;
  sem_wait(&empty);
  pthread_mutex_lock(&lock);
  usleep(20);
  sprintf(str, "%d", id);
  strcpy(logbuf[count], str);
  count = (count >= MAX_BUFFER_SLOT) ? count : (count + 1); /* Only increase count to size MAX_BUFFER_SLOT*/
  printf("wrlog(): %d \n", id);
  pthread_mutex_unlock(&lock);
  return 0;
}

void flushlog()
{
  int i;
  char nullval[MAX_LOG_LENGTH];

  printf("flushlog()\n");
  sprintf(nullval, "%d", -1);
  for (i = 0; i < count; i++)
  {
    printf("Slot  %i: %s\n", i, logbuf[i]);
    strcpy(logbuf[i], nullval);
  }

  fflush(stdout);

  /*Reset buffer */
  int temp_count = count;
  count = 0;
  for (int i = 0; i < temp_count; i++)
  {
    sem_post(&empty);
  }

  return;
}

void *timer_start(void *args)
{
  while (1)
  {
    flushlog();
    /*Waiting until the next timeout */
    usleep(((struct _args *)args)->interval);
  }
}

int main()
{
  int i;
  count = 0;
  pthread_t tid[MAX_LOOPS];
  pthread_t lgrid;
  int id[MAX_LOOPS];

  sem_init(&empty, 0, 6);
  pthread_mutex_init(&lock, NULL);
  struct _args args;
  args.interval = 500e3;
  /*500 msec ~ 500 * 1000 usec */

  /*Setup periodically invoke flushlog() */
  pthread_create(&lgrid, NULL, &timer_start, (void *)&args);

  /*Asynchronous invoke task writelog */
  for (i = 0; i < MAX_LOOPS; i++)
  {
    id[i] = i;
    pthread_create(&tid[i], NULL, wrlog, (void *)&id[i]);
  }

  for (i = 0; i < MAX_LOOPS; i++)
    pthread_join(tid[i], NULL);

  sleep(5);

  return 0;
}
