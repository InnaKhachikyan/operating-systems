Some tasks handle the user input in one way (like infinitely asking for a valid input), while the others in some other way: I just added some diversity in the solutions, as the problems were similar to each other.

# Task 1

If the user types not numbers, the program will terminate.
I read the input in an infinite loop so the program will not do its work and/or terminate until the user gives us a positive integer.
As my var to store the input is int, the user cannot also give something larger than 2^32-1, but that case is not handled here. 
If the user gives a valid input (>0) the loop breaks and we go on with the main logic, otherwise it says invalid input and prompt message comes again.


After reading the user's provided int, I allocate dynamically with malloc array of that size. Then check if malloc wasn't successful, perror and return 1. Otherwise prompt message again asking the user to input n integers (instead of n the integer they gave us earlier). Then in a loop I scan all the integers (if more integers are given, they are just discarded), and store them in the array. After, with a loop the sum is calculated and printed.
In the end we doo free() to free the dynamically allocated memory, and assign NULL to the dangling pointer.

Edited: I added a check for the maximum value acceptable, SIZE_MAX which belongs to the stdint.h and specifies the maximum size that malloc/calloc/realloc can accept (max value of the size_t). SIZE_MAX/sizeof(int) reassures that memory with the input given by the user can be allocated.


# Task 2

The initial logic is the same as in the task1: if not a number printed, the program terminates, if not a positive integer given, the user is notified and asked again to type a number. 
Dynamic memory allocation with calloc, then check if the memory was successfully allocated, if no - perror and return 1.
Printing the values of the array, all 0-s printed.
Then scanning the values given by the user into the array and calculating the average.
Printing the average with high precision.
And in the end I free() the memory and nullify the dangling pointer.


# Task 3

Dynamic allocation with the corresponding check. 10 values scaned, values written in the array.
arr resized with the help of realloc(). 
The array values printed after realloc.


# Task 4

In task 4 I defined the sizes with macros, just to make it easily changable if necessary.
I declared the double pointer to char as global, in order to use it in the free_mem function later. Also I stored str_allocated to trace how many strings have been allocated to be able to free them at any point, the free_mem function is registered via atexit. In order to be able to use the free_mem at any point, I first assign to null all the strings, so that if at any point of allocation any string malloc fails, I return 1 from main knowing that whatever was already allocated will be freed in free_mem (freeing nullified memory is fine).
I prompt a message and scan 3 strings, limiting the input to 49 chars (as the 50-th one should be \0).
Scan the messages provided by the user in the array, then print them, then realloc the array with the new size.
Again nullify the new cells, so that free_mem can free those at any point when anything goes wrong. 
Then allocate dynamically memory.
Prompt message again asking from the user NEW_SIZE-SIZE messages, scanning them, storing in the array, and printing.
In the end there is no need to free anything manually as after return 0 the registered free_mem function will free all the allocated memory and nullify the dangling pointers.

Edited: Initially I did ptr_str = realloc... That would work but maybe not correct, because if the realloc failed, it would return NULL and the ptr_str would be lost, while my program registered free_mem with atexit. So I changed and assigned the return of the realloc to a new double char pointer, so that if something goes wrong, free_mem is called and frees all the necessary memory.


# Task 5

Prompting message, reading input number from the user. 
Dynamic allocation with check whether it was successful.
Prompting message again, reading inputs and storing in the array of doubles.
With a single loop calculating the highest and the lowest grades, printing out.
We assume that the grades range is [0,100].
In the end freeing the memory and nullifying the pointer.


# Task 6

my_realloc

This version completes the task via the function malloc_usable_size function which returns us how many bytes are actually allocated with this pointer.
It checks if the pointer is NULL, behaves just like malloc with the given size.
If the given size is 0, it behaves like the ordinary free function.

Then it gets the size of the allocated memory via the function malloc_usable_size, to know how many bytes should be copied. 
Next, we allocate memory with malloc and new size and check whether it was successful.
Next we do copy: if old_size is less than new size, we copy old_size number of bytes, otherwise (if the user wanted to shrink the memory), we copy new_size number of bytes with memcpy.

In the end the pointer provided by the user is freed and nullified and the new_ptr is returned.


my_realloc2

I was trying to get the same functionality without using malloc_usable_size, but via getting the size from the headers that malloc function stores right before the pointer it returns.
If I understood correctly this behavior is specific to glibc:
If malloc returned some pointer ptr, 8 bytes before it we may find the size of the allocated memory (which the free function uses to free the memory). However together with the size there are also stored 3 flags (previous-in-use, is-mapped, non-main).
Actually I don't know the meaning of the last 2.
But what matters is that these 3 flags are stored in the least significant bits (regardless of whether it is a big or little endian), and to get rid of those flags and get the actual size I tried doing old_size BITWISE AND NOT(0x07). 
All the other steps are similar to the previous reallocator: my_realloc.

This one works too, however when I print the size of the allocated memory in the function via malloc_usable_size and print the old_size that I calculated with the help of the headers, those differ in size. I didn't run huge amount of tests, but what I ran so far show that the my calculated size is 8 bytes more than the malloc_usable_size shows.

Will try some more experiments on this.


# Task 7

alligned_malloc should return an alligned pointer after allocating memory. 
First of all I put some guards for the parameters, and return NULL if any of them are invalid or will overflow size_t type if I allocate alligned memory (SIZE_MAX shows the maximum value for size_t, which  is the maximum memory malloc can allocate).
I calculate the actual size as the 
size + (allignment - 1) + sizeof(void*)

the void pointer size is necessary as this will be my header, I need to store the original pointer provided by malloc, in order to be able to find it in the alligned_free function later and to pass it to the ordinary free function. 
Why allignment - 1: because if the pointer is not a multiple of the allignment, maximum extra storage we will need to make it alligned is (allignment - 1) depending on what remainder we got.
Again a guard, if actual size is bigger than the max size size_t can have as a value, then we cannot do malloc, return NULL.

Next we allocate memory with ordinary malloc and the actual size calculated, check if it was successfully allocated.

Then we should compute the new_ptr which should be alligned correspondingly to the user's request, and which we will return in the end.
It is worth mentioning that we ALWAYS add header and always shift the pointer (even if the pointer rturned by malloc is actually a multiple of the given allignment), because the alligned_free will work with that header, it should not "guess" whether the memory pointer has been shifted or no, whether there is a header added or no, it knows by default that before the pointer given to it there is the original pointer returned by malloc, which should be passed to ordinary free() function.

In order to find out how many bytes we should shift the pointer we calculate with modulo the rem, then extra bytes will make (allignment - rem) % allignment (which will cover also the case when rem was 0).

new_ptr will become the offset + extra_bytes calculated.
It remains to store the original pointer right before the new_ptr.
I chose to store only the original pointer, no additional information (I don't know whether any other info would be necessary here, so stored the minimal necessary for now), so only sizeof void pointer bytes are necessary (which typically is 8 bytes, but to be safe I wrote everywhere sizeof(void*).

I store the ptr (original pointer) right before the new_ptr which is already alligned memory and return new_ptr.

The alligned_free function "knows" that whatever pointer it is given, right before it the original pointer is stored. So it copoies the value of that pointer, and passes it to the ordinary free function. Here as well for the arithmetic I used sizeof void pointer to be on the safe side.





