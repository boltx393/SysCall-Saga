#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define N 5  

bool choosing[N] = {false};
int number[N] = {0};

void lock(int i) {
    int max = 0, j;

    choosing[i] = true;
    for (j = 0; j < N; j++) 
    {
        if (number[j] > max) 
        {
            max = number[j];
        }
    }
    number[i] = max + 1;
    choosing[i] = false;

    for (j = 0; j < N; j++) 
    {
        while (choosing[j]);
        while ((number[j] != 0) && ((number[j] < number[i]) || ((number[j] == number[i]) && (j < i))));
    }
}

void unlock(int i) 
{
    number[i] = 0;  
}

void* threadFunction(void* arg) {
    int threadId = *(int*)arg;

    lock(threadId);
    printf("Thread %d entered the critical section.\n", threadId);
    unlock(threadId);
    return NULL;
}

int main() {
    pthread_t threads[N];
    int threadIds[N];

    for (int i = 0; i < N; i++) 
    {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]);
    }
    for (int i = 0; i < N; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
