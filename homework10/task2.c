#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define NUM_WITHDRAW_THREADS 5
#define NUM_DEPOSIT_THREADS 5
#define NUM_ITER 10000

long long balance = 0;
pthread_spinlock_t spinlock;
pthread_mutex_t mutex_lock;
int mode_short;

void *deposit_spin(void* arg) {
	for(int i = 0; i < NUM_ITER; i++) {
		pthread_spin_lock(&spinlock);
		if(mode_short == 0) {
			usleep(100);
		}
		balance++;
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

void *deposit_mutex(void* arg) {
	for(int i = 0; i < NUM_ITER; i++) {
		if(mode_short == 0) {
			usleep(100);
		}
		pthread_mutex_lock(&mutex_lock);
		balance++;
		pthread_mutex_unlock(&mutex_lock);
	}
	return NULL;
}

void *withdraw_spin(void* arg) {
	for(int i = 0; i < NUM_ITER; i++) {
		if(mode_short == 0) {
			usleep(100);
		}
		pthread_spin_lock(&spinlock);
		balance--;
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

void *withdraw_mutex(void* arg) {
	for(int i = 0; i < NUM_ITER; i++) {
		if(mode_short == 0) {
			usleep(100);
		}
		pthread_mutex_lock(&mutex_lock);
		balance--;
		pthread_mutex_unlock(&mutex_lock);
	}
	return NULL;
}

int main(int args, char *argv[]) {
	if(args < 3) {
		printf("Correct usage %s <mode> (mutex/spin) <method> (short/long)\n", argv[0]);
		return 1;
	}

	pthread_t *deposit_threads = (pthread_t*)malloc(sizeof(pthread_t)*NUM_DEPOSIT_THREADS);
	if(!deposit_threads) {
		perror("malloc");
		return 1;
	}

	pthread_t *withdraw_threads = (pthread_t*)malloc(sizeof(pthread_t)*NUM_WITHDRAW_THREADS);
	if(!withdraw_threads) {
		perror("malloc");
		free(deposit_threads);
		deposit_threads = NULL;
		return 1;
	}

	char *mode = argv[1];
	if(strcmp(argv[2], "short") == 0) {
		mode_short = 1;
	}
	else if(strcmp(argv[2], "long") == 0) {
		mode_short = 0;
	}
	else {
		printf("Enter a valid method short OR long\n");
		return 1;
	}

	if(strcmp(mode, "mutex") == 0) {
		pthread_mutex_init(&mutex_lock, NULL);
		for(int i = 0; i < NUM_DEPOSIT_THREADS; i++) {
			if(pthread_create(&deposit_threads[i], NULL, deposit_mutex, NULL) != 0) {
				perror("pthread create");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_mutex_destroy(&mutex_lock);
				return 1;
			}
		}

		for(int i = 0; i < NUM_WITHDRAW_THREADS; i++) {
			if(pthread_create(&withdraw_threads[i], NULL, withdraw_mutex, NULL) != 0) {
				perror("pthread create");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_mutex_destroy(&mutex_lock);
				return 1;
			}
		}

		for(int i = 0; i < NUM_DEPOSIT_THREADS; i++) {
			if(pthread_join(deposit_threads[i], NULL) != 0) {
				perror("pthread join");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_mutex_destroy(&mutex_lock);
				return 1;
			}
		}
		
		for(int i = 0; i < NUM_WITHDRAW_THREADS; i++) {
			if(pthread_join(withdraw_threads[i], NULL) != 0) {
				perror("pthread join");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_mutex_destroy(&mutex_lock);
				return 1;
			}
		}
		pthread_mutex_destroy(&mutex_lock);
	}

	else if(strcmp(mode, "spin") == 0) {
		pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
		for(int i = 0; i < NUM_DEPOSIT_THREADS; i++) {
			if(pthread_create(&deposit_threads[i], NULL, deposit_spin, NULL) != 0) {
				perror("pthread create");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_spin_destroy(&spinlock);
				return 1;
			}
		}

		for(int i = 0; i < NUM_WITHDRAW_THREADS; i++) {
			if(pthread_create(&withdraw_threads[i], NULL, withdraw_spin, NULL) != 0) {
				perror("pthread create");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_spin_destroy(&spinlock);
				return 1;
			}
		}

		for(int i = 0; i < NUM_DEPOSIT_THREADS; i++) {
			if(pthread_join(deposit_threads[i], NULL) != 0) {
				perror("pthread join");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_spin_destroy(&spinlock);
				return 1;
			}
		}
		
		for(int i = 0; i < NUM_WITHDRAW_THREADS; i++) {
			if(pthread_join(withdraw_threads[i], NULL) != 0) {
				perror("pthread join");
				free(deposit_threads);
				free(withdraw_threads);
				deposit_threads = NULL;
				withdraw_threads = NULL;
				pthread_spin_destroy(&spinlock);
				return 1;
			}
		}
		pthread_spin_destroy(&spinlock);
	}

	else {
		printf("Enter valid mode: mutex OR spin");
		return 1;
	}

	printf("Balance is %lld\n", balance);

	free(deposit_threads);
	free(withdraw_threads);
	deposit_threads = NULL;
	withdraw_threads = NULL;

	return 0;
}
