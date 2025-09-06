#Assignment 1

I created an int a with the value 42, then passed its address to the int pointer ptr, printed both the address of the var with &a, and with the pointer.
Then I dereferenced ptr and assigned 23 to it, printed the new value.


#Assignment 2

I created an array of ints with values from 0 to 4 and printed the values incrementing the pointer by size of int at each iteration (via pointer arithmetic).
Using the same techniques I incremented each value of the array by 1, and printed those again using the pointer arithmetic, as arr is a pointer to the first element, adding 'i' at each iteration we get a pointer to the next int, dereference it and print the value.
Next, I printed the same array using arr[i] directly.


#Assignment 3

I created also an int b, passed the addresses of a and b to the function swap to swap their values. swap function stores the value of b in a temporary var, assigns the value of var a to the var b, then assigns the value of temp (which is the previous value of b) to the var a. 
Printing the values of a and b before and after swap, we see that the swap was successfully done.


#Assignment 4

I declared an int var without initialization, then created a pointer to int which stores the address of var, then created a double pointer which stores the address of the pointer of var. Dereferencing the double pointer twice, I initialized var to store the value 23 and printed it using the single and double pointers via dereferencing once/twice correspondingly.


#Assignment 5

I created an array of chars str[] = {Hello};
As we know both str and &str[0] are the same (pointer to the first element). We assign it to the pointer to char, then print the string using the same pointer arithmetic. I put the condition in the for and while loops != '\0' as this denotes the end of the string independent of its length, in my opinion more preferable then hardcoding i < 5. Using that condition I printed the whole string in the for loop and counted the number of chars in the while loop.

