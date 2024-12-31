#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// Shared buffer and associated variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Synchronization primitives
pthread_mutex_t mutex;
sem_t full, empty;

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) { // Produce 10 items
        item = rand() % 100; // Random item to produce
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex);

        // Add item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Signal that an item is available

        sleep(1); // Simulate production time
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) { // Consume 10 items
        sem_wait(&full); // Wait for an available item
        pthread_mutex_lock(&mutex);

        // Remove item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d at %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal that a slot is empty

        sleep(2); // Simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    // Initialize synchronization primitives
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0); // No items initially
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are empty initially

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
