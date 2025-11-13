#include <stdio.h>
#include <pthread.h>

void* thread_print(void* arg) {
	pthread_t tid = pthread_self();
	printf("Thread %lu is running\n", tid);
	return NULL;
}

int main(void) {
	pthread_t thread1, thread2, thread3;

	if(pthread_create(&thread1, NULL, &thread_print, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}

	if(pthread_create(&thread2, NULL, &thread_print, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}

	if(pthread_create(&thread3, NULL, &thread_print, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}

	if(pthread_join(thread1, NULL) != 0) {
		perror("pthread_join");
		return 1;
	}

	if(pthread_join(thread2, NULL) != 0) {
		perror("pthread_join");
		return 1;
	}

	if(pthread_join(thread3, NULL) != 0) {
		perror("pthread_join");
		return 1;
	}

	return 0;
}

