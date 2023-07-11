#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

int readCount = 0;
int readIterations = 0;
int writeIterations = 0;
sem_t mutex, db;

void *reader(void *arg) {
    while (readIterations < 5) {
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1)
            sem_wait(&db);
        sem_post(&mutex);

        // Critical section (reading)
        printf("Reader reading...\n");

        sem_wait(&mutex);
        readCount--;
        if (readCount == 0)
            sem_post(&db);
        sem_post(&mutex);

        readIterations++;
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    while (writeIterations < 5) {
        sem_wait(&db);

        // Critical section (writing)
        printf("Writer writing...\n");

        sem_post(&db);

        writeIterations++;
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

    pthread_t readerThread, writerThread;
    pthread_create(&readerThread, NULL, reader, NULL);
    pthread_create(&writerThread, NULL, writer, NULL);

    // Wait for the threads to finish
    pthread_join(readerThread, NULL);
    pthread_join(writerThread, NULL);

    // Cleanup
    sem_destroy(&mutex);
    sem_destroy(&db);

    return 0;
}