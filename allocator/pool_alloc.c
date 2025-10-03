#include <stdio.h>

#define	MIN_EXP 4
#define MAX_EXP 16
#define CLASSES (MAX_EXP - MIN_EXP + 1)

struct mem_node {
	void *ptr;
	struct mem_node *next;
};

static struct mem_node pool[CLASSES];

static inline int is_pow_2(size_t size) {
	return (n & (n-1) == 0);
}

size_t pow(size_t base, size_t exp) {
	if(exp == 0) {
		return 1;
	}
	size_t half = pow(base, exp/2);
	if(exp % 2 == 1) {
		return base * half * half;
	}
	return half * half;
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

	size_t length = num_blocks * pow(2, exponent);
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	// I should prepare nodes for blocks of memory to make a linked list and add in the array [exponent]

}


void* my_alloc(size_t size) {
	if(size <= 0) {
		return NULL;
	}
	
	int exponent = ceil_log2(size);
	if(pool[exponent] == NULL) {
		init_slab(exponent);
	}
	
	return NULL;
}

