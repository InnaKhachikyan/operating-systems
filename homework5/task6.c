#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>

void* my_realloc(void* ptr, size_t new_size) {

	if(ptr == NULL) {
		return malloc(new_size);
	}

	if(new_size == 0) {
		free(ptr);
		ptr = NULL;
		return NULL;
	}

	size_t old_size = malloc_usable_size(ptr);
	void *new_ptr = malloc(new_size);
	if(!new_ptr) {
		return NULL;
	}
	size_t copy = old_size < new_size ? old_size : new_size;

	memcpy(new_ptr, ptr, copy);
	free(ptr);
	ptr = NULL;
	return new_ptr;
}

void* my_realloc2(void* ptr, size_t new_size) {

        if(ptr == NULL) {
                return malloc(new_size);
        }

        if(new_size == 0) {
                free(ptr);
                ptr = NULL;
                return NULL;
        }

        //size_t old_size = (size_t)*((uint8_t*)(ptr-8));
        size_t old_size;
        memcpy(&old_size, (uint8_t*)(ptr) - 8, 8);
        old_size = old_size & (~0x07);

        printf("old size by malloc_usable %ld\n", malloc_usable_size(ptr));
        printf("Size is %ld\n", old_size);
        void *new_ptr = malloc(new_size);
        if(!new_ptr) {
                return NULL;
        }
        size_t copy = old_size < new_size ? old_size : new_size;

        memcpy(new_ptr, ptr, copy);
        free(ptr);
        ptr = NULL;
        return new_ptr;
}


int main(void) {

	int *ptr = (int*)malloc(sizeof(int)*16);
	if(!ptr) {
		perror("malloc");
		return 1;
	}
	for(int i = 0; i < 16; i++) {
		ptr[i] = i;
	}

	int *tmp = my_realloc(ptr, 32 * sizeof(int));
	if(!tmp) {
		printf("reallocation failed");
		return 1;
	}

	ptr = tmp;

	for(int i = 16; i < 32; i++) {
		ptr[i] = i;
	}

	for(int i = 0; i < 32; i++) {
		printf("ptr[%d] %d\n", i, ptr[i]);
	}

	free(ptr);
	ptr = NULL;
	return 0;

}
