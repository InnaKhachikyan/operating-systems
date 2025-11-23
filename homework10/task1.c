#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define NUM_INC 1000000

long long counter = 0;
pthread_spinlock_t spinlock;
pthread_mutex_t mutex_lock;

void *inc_spin(void*) {
	for(int i = 0; i < NUM_INC; i++) {
		pthread_spin_lock(&spinlock);
		counter++;
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

void *inc_mutex(void*) {
	for(int i = 0; i < NUM_INC; i++) {
		pthread_mutex_lock(&mutex_lock);
		counter++;
		pthread_mutex_unlock(&mutex_lock);
	}
	return NULL;
}

void *inc_unsync(void*) {
	for(int i = 0; i < NUM_INC; i++){
		counter++;
	}
	return NULL;
}

int main(int args, char *argv[]) {

	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * NUM_THREADS);
	if(!threads) {
		perror("malloc");
		return 1;
	}


	if(args < 2) {
		printf("Correct usage: %s <mode> (nosync/mutex/spin)\n", argv[0]);
		free(threads);
		threads = NULL;
		return 1;
	}

	char *mode = argv[1];

	if(strcmp(mode, "nosync") == 0) {
		for(int i = 0; i < NUM_THREADS; i++) {
			if(pthread_create(&threads[i], NULL, inc_unsync, NULL) != 0) {
				perror("pthread create");
				free(threads);
				threads = NULL;
				return 1;
			}
		}

		for(int i = 0; i < NUM_THREADS; i++) {
			if(pthread_join(threads[i], NULL) != 0) {
				perror("pthread join");
				free(threads);
				threads = NULL;
				return 1;
			}
		}
		printf("Expected value: %lld\n", (long long)NUM_THREADS * NUM_INC);
		printf("Counter is: %lld\n", counter);
	}

	else if(strcmp(mode, "mutex") == 0) {
		pthread_mutex_init(&mutex_lock, NULL);
		for(int i = 0; i < NUM_THREADS; i++) {
			if(pthread_create(&threads[i], NULL, inc_mutex, NULL) != 0) {
				perror("pthread create");
				free(threads);
				threads = NULL;
				pthread_mutex_destroy(&mutex_lock);
				return 1;
			}
		}

		for(int i = 0; i < NUM_THREADS; i++) {
			if(pthread_join(threads[i], NULL) != 0) {
				perror("pthread join");
				free(threads);
				threads = NULL;
				pthread_mutex_destroy(&mutex_lock);
				return 1;
			}
		}
		pthread_mutex_destroy(&mutex_lock);

		printf("Expected value: %lld\n", (long long)NUM_THREADS * NUM_INC);
		printf("Counter is: %lld\n", counter);
	}

	else if(strcmp(mode, "spin") == 0) {
		pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
		for(int i = 0; i < NUM_THREADS; i++) {
			if(pthread_create(&threads[i], NULL, inc_spin, NULL) != 0) {
				perror("pthread create");
				free(threads);
				threads = NULL;
				pthread_spin_destroy(&spinlock);
				return 1;
			}
		}

		for(int i = 0; i < NUM_THREADS; i++) {
			if(pthread_join(threads[i], NULL) != 0) {
				perror("pthread join");
				free(threads);
				threads = NULL;
				pthread_spin_destroy(&spinlock);
				return 1;
			}
		}
		pthread_spin_destroy(&spinlock);

		printf("Expected value: %lld\n", (long long)NUM_THREADS * NUM_INC);
		printf("Counter is: %lld\n", counter);
	}

	else {
		printf("Enter a valid mode: nosync OR mutex OR spin\n");
		return 1;
	}

	free(threads);
	threads = NULL;
	return 0;
}

