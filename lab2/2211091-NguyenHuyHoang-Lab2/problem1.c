#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define MAXMOVIES 1682
#define MAXUSERS 943
// đọc file
void readInput(char *filename, int (*vector)[MAXMOVIES][MAXUSERS])
{
  FILE *file = fopen(filename, "r");
  int userID, movieID, userRate, timestamp;
  while (fscanf(file, "%d\t%d\t%d\t%d\n", &userID, &movieID, &userRate, &timestamp) == 4)
  {
    (*vector)[movieID - 1][userID - 1] = userRate;
  }
  fclose(file);
}
int main()
{
  pid_t child1, child2, parent;
  int size_total = MAXMOVIES * MAXUSERS * sizeof(int);
  int(*vector)[MAXMOVIES][MAXUSERS];
  double final_ave = 0;
  int sum_userRate[MAXMOVIES] = {0};
  int user_rate_num[MAXUSERS] = {0};
  int shmid;
  shmid = shmget(IPC_PRIVATE, size_total, IPC_CREAT | 0666); // tạo một segmen memory , shmid là ID
  vector = (int(*)[MAXMOVIES][MAXUSERS])shmat(shmid, NULL, 0);
  memset(vector, 0, size_total);
  child1 = fork();
  if (child1 == 0)
  {
    readInput("movie-100k_1.txt", vector);
  }
  else
  {
    child2 = fork();
    if (child2 == 0)
    {
      readInput("movie-100k_2.txt", vector);
    }
    else
    {
      wait(NULL);
      wait(NULL);
      // đợi để 2 quá trình con chạy xong
      double ave_arr[MAXMOVIES] = {0};
      for (int movie = 0; movie < MAXMOVIES; movie++)
      {
        int userRate = 0;
        int sum_userRate = 0;
        for (int user = 0; user < MAXUSERS; user++)
        {
          if ((*vector)[movie][user] > 0)
          {
            userRate++;
            sum_userRate += (*vector)[movie][user];
          }
        }
        double ave_userRate = (double)sum_userRate / userRate;
        ave_arr[movie] = ave_userRate;
      }
      FILE *file = fopen("moviesRating.txt", "w");
      for (int i = 0; i < MAXMOVIES; i++)
      {
        fprintf(file, "Movie %d has rated %f\n", i + 1, ave_arr[i]);
      }
    }
  }

  return 0;
}