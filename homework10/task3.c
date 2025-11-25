#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFFER_SIZE 8
#define PRODUCERS 8
#define CONSUMERS (PRODUCERS/2)
#define NUM_ITER (PRODUCERS * 1000)

int in_pos = 0;
int out_pos = 0;

int buffer[BUFFER_SIZE];
sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void* produce(void* arg) {
	for(int i = 0; i < NUM_ITER/PRODUCERS; i++) {
		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);
		buffer[in_pos] = i;
		in_pos = (in_pos + 1) % BUFFER_SIZE;
		int sem_value;
		sem_getvalue(&full_slots, &sem_value);
		printf("[Producers] elements in buffer %d\n", sem_value);
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);
	}
	return NULL;
}

void* consume(void* arg) {
	for(int i = 0; i < NUM_ITER/CONSUMERS; i++) {
		sem_wait(&full_slots);
		pthread_mutex_lock(&buffer_mutex);
		printf("READ: %d\n",buffer[out_pos]);
		out_pos = (out_pos + 1) % BUFFER_SIZE;
		int sem_value;
		sem_getvalue(&full_slots, &sem_value);
		printf("[Consumers] elements in buffer %d\n", sem_value);
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&empty_slots);
	}
	return NULL;
}

int main(void) {

	
	pthread_t *producers = (pthread_t*)malloc(sizeof(pthread_t) * PRODUCERS);
	if(!producers) {
		perror("malloc");
		return 1;
	}

	pthread_t *consumers = (pthread_t*)malloc(sizeof(pthread_t) * CONSUMERS);
	if(!consumers) {
		perror("malloc");
		free(producers);
		producers = NULL;
		return 1;
	}

	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);

	for(int i = 0; i < PRODUCERS; i++) {
		if(pthread_create(&producers[i], NULL, produce, NULL) != 0) {
			perror("pthread create");
			free(producers);
			free(consumers);
			producers = NULL;
			consumers = NULL;
			pthread_mutex_destroy(&buffer_mutex);
			sem_destroy(&empty_slots);
			sem_destroy(&full_slots);
			return 1;
		}
	}

	for(int i = 0; i < CONSUMERS; i++) {
		if(pthread_create(&consumers[i], NULL, consume, NULL) != 0) {
			perror("pthread create");
			free(producers);
			free(consumers);
			producers = NULL;
			consumers = NULL;
			pthread_mutex_destroy(&buffer_mutex);
			sem_destroy(&empty_slots);
			sem_destroy(&full_slots);
			return 1;
		}
	}

	for(int i = 0; i < PRODUCERS; i++) {
		if(pthread_join(producers[i], NULL) != 0) {
			perror("pthread join");
			free(producers);
			free(consumers);
			producers = NULL;
			consumers = NULL;
			pthread_mutex_destroy(&buffer_mutex);
			sem_destroy(&empty_slots);
			sem_destroy(&full_slots);
			return 1;
		}
	}

	for(int i = 0; i < CONSUMERS; i++) {
		if(pthread_join(consumers[i], NULL) != 0) {
			perror("pthread join");
			free(producers);
			free(consumers);
			producers = NULL;
			consumers = NULL;
			pthread_mutex_destroy(&buffer_mutex);
			sem_destroy(&empty_slots);
			sem_destroy(&full_slots);
			return 1;
		}
	}

	free(producers);
	free(consumers);
	producers = NULL;
	consumers = NULL;
	pthread_mutex_destroy(&buffer_mutex);
	sem_destroy(&empty_slots);
	sem_destroy(&full_slots);
	return 0;
}

