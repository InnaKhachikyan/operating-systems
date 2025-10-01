#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void* alligned_malloc(size_t size, size_t allignment) {
	if(size == 0 || allignment == 0 || size > SIZE_MAX - sizeof(void*)) {
		return NULL;
	}

	size_t actual_size = size + (allignment-1) + sizeof(void*);
	if(actual_size > SIZE_MAX) {
		return NULL;
	}
	void *ptr = malloc(actual_size);
	if(!ptr) {
		return NULL;
	}

	void *new_ptr;
	uint8_t *offset = (uint8_t*)ptr + sizeof(void*);	
	size_t rem = (uintptr_t)offset % allignment;
	size_t extra_bytes = (allignment - rem) % allignment;
	new_ptr = offset + extra_bytes;
	
	memcpy((uint8_t*)new_ptr - sizeof(void*), &ptr, sizeof(void*));

	return (void*)new_ptr;	
}

void alligned_free(void* ptr) {
	if(ptr == NULL) {
		return;
	}
	void* original_pointer;
       	memcpy(&original_pointer, (uint8_t*)ptr - sizeof(void*), sizeof(void*));
	free(original_pointer);
	return;
}

int main(void) {

	int* arr = alligned_malloc(45, 16);
	if(!arr) {
		perror("malloc");
		return 1;
	}

	printf("Pointer of arr is %p\n", arr);
	printf("mod %ld\n", (uintptr_t)arr%16);

	return 0;
}
