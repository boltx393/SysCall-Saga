#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

// Global resources
pthread_mutex_t mutexA, mutexB;

void* threadA(void* arg) {
    // Acquire mutex A
    pthread_mutex_lock(&mutexA);
    printf("Thread A acquired mutex A\n");

    // Introduce some delay to create a deadlock scenario
    sleep(1);

    printf("Thread A waiting for mutex B\n");

    // Attempt to acquire mutex B
    pthread_mutex_lock(&mutexB);
    printf("Thread A acquired mutex B\n");

    // Release mutexes
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);

    return NULL;
}

void* threadB(void* arg) {
    // Acquire mutex B
    pthread_mutex_lock(&mutexB);
    printf("Thread B acquired mutex B\n");

    // Introduce some delay to create a deadlock scenario
    sleep(1);

    printf("Thread B waiting for mutex A\n");

    // Attempt to acquire mutex A
    pthread_mutex_lock(&mutexA);
    printf("Thread B acquired mutex A\n");

    // Release mutexes
    pthread_mutex_unlock(&mutexA);
    pthread_mutex_unlock(&mutexB);

    return NULL;
}

int main() {
    // Initialize mutexes
    pthread_mutex_init(&mutexA, NULL);
    pthread_mutex_init(&mutexB, NULL);

    // Create threads
    pthread_t tidA, tidB;
    pthread_create(&tidA, NULL, threadA, NULL);
    pthread_create(&tidB, NULL, threadB, NULL);

    // Wait for threads to complete
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    // Destroy mutexes
    pthread_mutex_destroy(&mutexA);
    pthread_mutex_destroy(&mutexB);

    return 0;
}
