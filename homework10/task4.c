#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 1000

pthread_t threadA, threadB, threadC;
sem_t semA, semB, semC;
const char A = 'A';
const char B = 'B';
const char C = 'C';

void* thread_job(void *arg) {
	char th = *((char*)arg);
	if(th == 'A') {
		for(int i = 0; i < N; i++) {
			sem_wait(&semA);
			printf("Thread A %d\n", i);
			sem_post(&semB);
		}
	}
	else if(th == 'B') {
		for(int i = 0; i < N; i++) {
			sem_wait(&semB);
			printf("Thread B %d\n", i);
			sem_post(&semC);
		}
	}
	else {
		for(int i = 0; i < N; i++) {
			sem_wait(&semC);
			printf("Thread C %d\n", i);
			sem_post(&semA);
		}
	}
	return NULL;
}

int main(void) {

	sem_init(&semA, 0, 1);
	sem_init(&semB, 0, 0);
	sem_init(&semC, 0, 0);

	if(pthread_create(&threadA, NULL, thread_job, (void*)(&A)) != 0) {
		perror("pthread create");
		sem_destroy(&semA);
		sem_destroy(&semB);
		sem_destroy(&semC);
		return 1;
	}

	if(pthread_create(&threadB, NULL, thread_job, (void*)(&B)) != 0) {
		perror("pthread create");
		sem_destroy(&semA);
		sem_destroy(&semB);
		sem_destroy(&semC);
		return 1;
	}

	if(pthread_create(&threadC, NULL, thread_job, (void*)(&C)) != 0) {
		perror("pthread create");
		sem_destroy(&semA);
		sem_destroy(&semB);
		sem_destroy(&semC);
		return 1;
	}

	if(pthread_join(threadA, NULL) != 0) {
		perror("pthread join");
		sem_destroy(&semA);
		sem_destroy(&semB);
		sem_destroy(&semC);
		return 1;
	}

	if(pthread_join(threadB, NULL) != 0) {
		perror("pthread join");
		sem_destroy(&semA);
		sem_destroy(&semB);
		sem_destroy(&semC);
		return 1;
	}

	if(pthread_join(threadC, NULL) != 0) {
		perror("pthread join");
		sem_destroy(&semA);
		sem_destroy(&semB);
		sem_destroy(&semC);
		return 1;
	}

	sem_destroy(&semA);
	sem_destroy(&semB);
	sem_destroy(&semC);
	return 0;
}
