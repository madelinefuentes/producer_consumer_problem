# Synchronizing Threads
**Threads** are basic components of a process; many can run in a single process. Each **thread behaves as a process** and can also be viewed as an abstraction for a single running program. The main difference being that threads share the same address space and thus can share data between them.

For an example of how threads work within a process, consider a task such as adding two large arrays together. With threads working on different parts of the array at once, this can be done much faster than with a single running instance.

However, problems arrive when threads update and access a shared variable. If threads are not synchronized properly, we may experience undeterministic results. Such is the premise of the **Producer Consumer Problem**, or the **Bounded Buffer Problem**.

## The Producer Consumer Problem
We have a producer process that puts items into a shared buffer, and a consumer process that consumes items from the buffer. A producer cannot produce elements into a full buffer and a consumer cannot take items from an empty buffer.

Threads that do not execute **critical sections** of the code (ex. sections that change a shared value) **atomically**, that is all at once, can lead to issues. Say a producer A puts an item into the buffer and fills its capacity and before it can update its size, it's switched to a producer B. Since A did not update the size before the switch, B will put an item into the buffer even though it is full.

This implementation ensures that a thread does not switch to another thread in a critical section, consumes from an empty buffer, or produces items in a full buffer through the use of **locks** and **condition variables**. A **circular queue** is used for the buffer.

## Instructions
This code utilizes the POSIX pthreads library for Linux. Provide as command line arguments: number of producers, number of consumers, sleep time of producers, sleep time of consumers, and items to be produced into buffer and consumed.

Compile with -pthread

10 10 1000 1000 20

10 producers, 10 consumers, each sleep for 1000ms, produce and consume 20 items in buffer

writes results to output.txt
