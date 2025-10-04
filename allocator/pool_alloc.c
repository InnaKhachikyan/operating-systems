#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define	MIN_EXP 4
#define MAX_EXP 16
#define CLASSES (MAX_EXP - MIN_EXP + 1)

struct mem_node {
	void *ptr;
	struct mem_node *next;
};

static struct mem_node *free_lists[CLASSES];

static inline int is_pow_2(size_t size) {
	return (size & (size-1) == 0);
}

static inline int ceil_log2(size_t size) {
	int index = 0;
	if(size <= 1) {
		return index;
	}
	if(is_pow_2(size) == 1) {
		index++;
	}
	index += 64 - __builtin_clzll(size - 1);
	return index; //GCC builtin function to count leading zeros in 64-bit machine
}

void init_slab(int exponent) {
	int num_blocks =
		(exponent <= 8) ? 64 :
		(exponent <= 11) ? 32 :
		(exponent <= 13) ? 16 : 8;

	size_t num_bytes = (size_t)1ULL << exponent;
	size_t length = num_blocks * num_bytes;
	void *slab = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(slab == MAP_FAILED) {
		perror("mmap");
		return;
	}
	uint8_t *pointer = (uint8_t*)slab;

	struct mem_node *next_node = NULL;
	struct mem_node *current = NULL;
	for(int i = 0; i < num_blocks; i++) {
		current->ptr = (uint8_t*)pointer + i*num_bytes;
		current->next = next_node;
		current = next_node;
		next_node = NULL;
	}


}


void* p_alloc(size_t size) {
	if(size == 0) {
		return NULL;
	}
	
	int exponent = ceil_log2(size);
	if(free_lists[exponent] == NULL) {
		init_slab(exponent);
	}
	
	return NULL;
}

