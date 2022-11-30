#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD 3
#define ROWS 3
#define COLS 4

struct arrays
{
    int arr1[4];
    int arr2[4];
};

void *fun(void *args)
{
    struct arrays *obj1 = (struct arrays *)args;
    int *result = (int *)malloc(4 * sizeof(int));
    for (size_t i = 0; i < 4; i++)
    {
        result[i] = obj1->arr1[i] + obj1->arr2[i];
    }

    pthread_exit((void *)result);
}

int main()
{
    int mat_A[ROWS][COLS] = {1, 2, 3, 4, 1, 6, 3, 2, 9, 2, 3, 4};
    int mat_B[ROWS][COLS] = {5, 4, 6, 2, 4, 1, 2, 1, 0, 7, 5, 2};
    int sum[ROWS][COLS];

    struct arrays obj[MAX_THREAD];
    pthread_t t[MAX_THREAD];

    for (size_t i = 0; i < MAX_THREAD; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            obj[i].arr1[j] = mat_A[i][j];
            obj[i].arr2[j] = mat_B[i][j];
        }
        pthread_create(&t[i], NULL, fun, (void *)&obj[i]);
    }

    for (size_t i = 0; i < MAX_THREAD; i++)
    {
        void **res;
        pthread_join(t[i], res);
        for (size_t k = 0; k < 4; k++)
        {
            sum[i][k] = (*(int **)res)[k];
        }
        free(*(int **)res);
    }
}