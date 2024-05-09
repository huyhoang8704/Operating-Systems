#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }

    int n = atoi(argv[1]);
    // clock_t start = clock();
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    // clock_t end = clock();
    // double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("sum_serial = %lld", sum);
    return 0;
}