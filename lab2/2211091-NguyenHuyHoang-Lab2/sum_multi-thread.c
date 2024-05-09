#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct
{
    long long start;
    long long end;
} Scope;
void *sumofthread(void *arg)
{
    Scope *range = (Scope *)arg;
    long long sum = 0;
    for (long long i = range->start; i <= range->end; i++)
    {
        sum += i;
    }
    long long *result = malloc(sizeof(long long));
    *result = sum;
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error\n");
        return 1;
    }
    long long n = atoll(argv[2]);
    long long num_thread = atoll(argv[1]);
    // clock_t start = clock();
    pthread_t threads[num_thread];
    Scope ranges[num_thread];

    for (long long i = 0; i < num_thread; i++)
    {
        ranges[i].start = i * n / num_thread + 1;
        ranges[i].end = (i + 1) * n / num_thread;
        pthread_create(&threads[i], NULL, sumofthread, &ranges[i]);
    }
    long long sum = 0;
    for (long long i = 0; i < num_thread; i++)
    {
        long long *temp;
        pthread_join(threads[i], (void **)&temp);
        sum += *temp;
        free(temp);
    }
    // clock_t end = clock();
    // double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("sum_multi-threads = %lld", sum);
    return 0;
}