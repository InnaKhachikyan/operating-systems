# Task 1

If the user types not numbers, the program will terminate.
I read the input in an infinite loop so the program will not do its work and/or terminate until the user gives us a positive integer.
As my var to store the input is int, the user cannot also give something larger than 2^32-1, but that case is not handled here. 
If the user gives a valid input (>0) the loop breaks and we go on with the main logic, otherwise it says invalid input and prompt message comes again.


After reading the user's provided int, I allocate dynamically with malloc array of that size. Then check if malloc wasn't successful, perror and return 1. Otherwise prompt message again asking the user to input n integers (instead of n the integer they gave us earlier). Then in a loop I scan all the integers (if more integers are given, they are just discarded), and store them in the array. After, with a loop the sum is calculated and printed.
In the end we doo free() to free the dynamically allocated memory, and assign NULL to the dangling pointer.


# Task 2

The initial logic is the same as in the task1: if not a number printed, the program terminates, if not a positive integer given, the user is notified and asked again to type a number. 
Dynamic memory allocation with calloc, then check if the memory was successfully allocated, if no - perror and return 1.
Printing the values of the array, all 0-s printed.
Then scanning the values given by the user into the array and calculating the average.
Printing the average with high precision.
And in the end I free() the memory and nullify the dangling pointer.


