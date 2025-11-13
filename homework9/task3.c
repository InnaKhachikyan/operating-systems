#include <stdio.h>
#include <pthread.h>

#define PRINT_SIZE 5

void *print_numbers(void *arg) {
	printf("Thread id: %lu \n", (unsigned long)pthread_self());
	for(int i = 0; i < PRINT_SIZE; i++) {
		printf("%d ", i+1);
	}
	printf("\n");
	return NULL;
}

int main(void) {

	pthread_t thread1, thread2, thread3;

	if(pthread_create(&thread1, NULL, &print_numbers, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}

	if(pthread_create(&thread2, NULL, &print_numbers, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}
	
	if(pthread_create(&thread3, NULL, &print_numbers, NULL) != 0) {
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

