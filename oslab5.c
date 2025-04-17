#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 5
int buffer[SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;
sem_t chopstick[SIZE];
void* producer(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        int item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % SIZE;
        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}
void* consumer(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;
        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}
void run_producer_consumer() {
    pthread_t prod, cons;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}
void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % SIZE;
    printf("Philosopher %d is thinking.\n", id);
    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);
    printf("Philosopher %d is eating.\n", id);
    sem_post(&chopstick[left]);
    sem_post(&chopstick[right]);
    printf("Philosopher %d finished eating.\n", id);
    return NULL;
}
void run_dining_philosophers() {
    pthread_t phil[SIZE];
    int ids[SIZE];
    for (int i = 0; i < SIZE; i++) {
        sem_init(&chopstick[i], 0, 1);
    }
    for (int i = 0; i < SIZE; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < SIZE; i++) {
        pthread_join(phil[i], NULL);
    }
    for (int i = 0; i < SIZE; i++) {
        sem_destroy(&chopstick[i]);
    }
}
int main() {
    int choice;
    printf("Choose an option:\n");
    printf("1. Producer-Consumer Problem\n");
    printf("2. Dining Philosophers Problem\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        run_producer_consumer();
    } else if (choice == 2) {
        run_dining_philosophers();
    } else {
        printf("Invalid choice!\n");
    }
    return 0;
}