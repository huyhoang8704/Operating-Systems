#include <stdio.h>
#include <pthread.h>
#define MAX_COUNT 10000
int count;
void *f_count(void *sid)
{
  int i;
  //! race condition
  for (i = 0; i < MAX_COUNT; i++)
  {
    count = count + 1;
  }
  printf("Thread %s : holding %d \n", (char *)sid, count);
  getc(stdin);
}
int fibonacci(int n){
}
int main(int argc, char *argv[])
{
  printf("Helloworld \n");
  pthread_t thread1, thread2;
  count = 0;
  /* Create independent threads each of which will execute function */
  pthread_create(&thread1, NULL, &f_count, "1");
  pthread_create(&thread2, NULL, &f_count, "2");
  // chờ thread1 thực hiện xong
  pthread_join(thread1, NULL);
  // chờ thread2 thực hiện xong
  pthread_join(thread2, NULL);
  getc(stdin);
  return 0;
}
