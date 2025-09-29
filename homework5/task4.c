#include <stdio.h>
#include <stdlib.h>

#define SIZE 3
#define NEW_SIZE 5
#define STR_SIZE 50

char **ptr_str;
int resized = 0;

void free_mem(void) {
	int limit = SIZE;
	if(resized == 1) {
		limit = NEW_SIZE;
	}
	for(int i = 0; i < limit; i++) {
		free(ptr_str[i]);
		ptr_str[i] = NULL;
	}
	free(ptr_str);
	ptr_str = NULL;
}

int main(void) {

	ptr_str = (char**)malloc(sizeof(char*)*SIZE);
	if(!ptr_str) {
		perror("malloc");
		return 1;
	}

	for(int i = 0; i < SIZE; i++) {
		ptr_str[i] = (char*)malloc(sizeof(char)*STR_SIZE);
		if(!ptr_str[i]) {
			perror("malloc");
			for(int j = 0; j < i; j++) {
				free(ptr_str[j]);
				ptr_str[j] = NULL;
			}
			free(ptr_str);
			ptr_str = NULL;
			return 1;
		}
	}	

	atexit(&free_mem);

	printf("Please enter 3 messages\n");

	for(int i = 0; i < SIZE; i++) {
		if(scanf("%49s", ptr_str[i]) != 1) {
			printf("Reading input failed\n");
			return 1;
		}
	}

	for(int i = 0; i < SIZE; i++) {
		printf("%s\n", ptr_str[i]);
	}

	ptr_str = (char**)realloc(ptr_str, sizeof(char*)*(NEW_SIZE));
	if(ptr_str == NULL) {
		perror("realloc");
		return 1;
	}
	for(int i = 0; i < NEW_SIZE - SIZE; i++) {
		ptr_str[SIZE + i] = (char*)malloc(sizeof(char)*STR_SIZE);
		if(!ptr_str[SIZE + i]) {
			perror("malloc");
			return 1;
		}
	}

	resized = 1;

	printf("please enter %d more messages\n", (NEW_SIZE - SIZE));
	for(int i = 0; i < NEW_SIZE - SIZE; i++) {
		if(scanf("%49s", ptr_str[SIZE +i]) != 1) {
			printf("Failed to read input");
			return 1;
		}
	}
	for(int i = 0; i < NEW_SIZE; i++) {
		printf("%s\n", ptr_str[i]);
	}


	return 0;
}
