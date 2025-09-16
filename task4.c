#include <pthread.h>
#include <stdio.h>

typedef struct {
    int *arr;
    int size;
    int res;
} Arr;

void* getSum(void* arr) {
    Arr* arg = (Arr*) arr;
    int sum = 0;
    for (int i = 0; i < arg->size; ++i) {
        sum += (arg->arr)[i];
    }
    arg->res = sum;
    return NULL;
}

int main() {
    pthread_t th;
    const int size = 10;
    int arr[size] = {1,2,3,4,5,6,7,8,9,10};
    Arr arg = {arr, size,  0};
    pthread_create(&th, NULL, getSum, &arg);
    pthread_join(th, NULL);
    printf("The sum is - %d\n", arg.res);
    return 0;
}