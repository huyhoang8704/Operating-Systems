#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int MAX_COUNT = 1e9;
static int count = 0;
pthread_mutex_t lock;

void *fcount(void *sid)
{
  int i;
  pthread_mutex_lock(&lock);
  for (i = 0; i < MAX_COUNT; i++)
  {
    count = count + 1;
  }
  pthread_mutex_unlock(&lock);
  printf("Thread %s: holding %d\n", (char *)sid, count);
  return NULL;
}

int main()
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, &fcount, "1");
  pthread_create(&thread2, NULL, &fcount, "2");

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
