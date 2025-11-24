#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define PRINTERS 4
#define NUM_JOBS 100

sem_t printers;
int active_printers_counter = 0;
pthread_mutex_t lock_counter;

void *printing_job(void *arg) {
	sem_wait(&printers);
	printf("Thread %d is printing\n", *((int*)arg));
	pthread_mutex_lock(&lock_counter);
	active_printers_counter++;
	printf("Active printers: %d\n", active_printers_counter);
	pthread_mutex_unlock(&lock_counter);
	usleep(10);
	pthread_mutex_lock(&lock_counter);
	active_printers_counter--;
	pthread_mutex_unlock(&lock_counter);
	sem_post(&printers);
	return NULL;
}

int main(void) {

	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * NUM_JOBS);
	if(!threads) {
		perror("malloc");
		return 1;
	}

	sem_init(&printers, 0, PRINTERS);
	pthread_mutex_init(&lock_counter, NULL);

	int thread_num = 0;
	for(int i = 0; i < NUM_JOBS; i++) {
		if(pthread_create(&threads[i], NULL, printing_job, (void*)&thread_num) != 0) {
			perror("pthread create");
			free(threads);
			threads = NULL;
			sem_destroy(&printers);
			pthread_mutex_destroy(&lock_counter);
			return 1;
		}
		thread_num++;
	}

	for(int i = 0; i < NUM_JOBS; i++) {
		if(pthread_join(threads[i], NULL) != 0) {
			perror("pthread join");
			free(threads);
			threads = NULL;
			sem_destroy(&printers);
			pthread_mutex_destroy(&lock_counter);
			return 1;
		}
	}

	free(threads);
	threads = NULL;
	sem_destroy(&printers);
	pthread_mutex_destroy(&lock_counter);
	return 0;
}
