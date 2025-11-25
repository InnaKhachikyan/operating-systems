### Task 1
The nosync version gives the wrong answer becasue of the race condition.
Example: let's say that the value of the counter is 100.
More than one thread, let's say 3 of them, read this value simultaneously and increment it to 101, write it back to memory, so instead of incrementing the counter to 103 together, they all increment it to 101. If Read-After-Write, Write-After-Write conditions are not met, that would lead to false results.
Spinlock and mutex solve this problem as thay protect the critical section, and one thread reads the var only after the other writes, AND writes after write. the locks ensure these.

![task 1 result screenshot](./task1.png)

### Task 2
For the short version spinlock is better, as the work is short it is better to wait in a busy loop, rather than sleep until the lock is released. Sleeping and waking up is not worth of the resources spent in such a short-term work.
For the long version with usleep(100) mutex is much better. When the job to be done is long, it is better to use mutex, to sleep until the lock is released rather than do a busy loop-waiting as it takes much resources.

![task 2 result screenshot](./task2.png)

### Task 3
The semaphore itself keeps the track of when the slots are empty/full, so the thread goes to sleep until the condition is met. It does not lock the critical section. For locking critical section we still need some locking mechanism, like mutex. Sempahore is for inter-thread (for this task) communication, so that they "know" when they can produce/consume, and when there is no job to do yet, and can go to sleep.

![task 3 result screenshot](./task3.png)

### Task 4
Using only sleep() is not reliable because we cannot control or predict how the OS scheduler interleaves threads or which thread will wake up first, so timing based delays do not guarantee any order. Semaphores solve this problem as they explicitly block and wake specific threads based on logical conditions, not on timing.

![task 4 result screenshot](./task4.png)

### Task 5
If we initialize the semaphore to 1, only 1 printing job will be done simultaneously.
The result of the program with semaphore initialized to 1

![task 5 test 1](./task5_test1.png)

If we initialize the semaphore to a huge number (greater than the printers available) we will allow that way for more threads being active simultaneously, so said: more jobs to be done than we have available printers. So, semaphore here define how many threads can be active simultaneously.
The result of the semaphore initialized to huge number

![task 5 test 2](./task5_test2.png)

The result of the main program (semaphore initialized to the number of printers).

![task 5 main](./task5.png)

