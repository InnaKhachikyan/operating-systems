# Task 1

I read the input in an infinite loop so the program will not do its work and/or terminate until the user gives us a valid input. As my var to store the input is int, the user cannot also give something larger than 2^32-1, but that case is not handled here. If the user gives a valid input (>0) the loop breaks and we go on with the main logic, otherwise it says invalid input and prompt message comes again.

After reading the user's provided int, I allocate dynamically with malloc array of that size. Then check if malloc wasn't successful, perror and return 1. Otherwise prompt message again asking the user to input n integers (instead of n the integer they gave us earlier). Then in a loop I scan all the integers (if more integers are given, they are just discarded), and store them in the array. After, with a loop the sum is calculated and printed.
In the end we doo free() to free the dynamically allocated memory, and assign NULL to the dangling pointer.


