#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define INCREMENTS 10000

int counter = 0; // shared resource among threads (stored in the process address space I guess?)

void *increment_thread(void *arg)
{
  for (int i = 0; i < INCREMENTS; i++)
  {
    // counter++ is not atomic
    // 1. Read value
    // 2. Increment the value
    // 3. Write back the new value in the location
    counter++;
  }

  // pthread_exit() is a function provided by the POSIX threads (pthreads) API
  // that terminates the calling thread in an orderly fashion.
  // When a thread calls pthread_exit(), it cleans up its own resources and
  // may return a value to any thread that later calls pthread_join() on it.

  // Why NULL?
  // NULL => I have nothing to return
  // But you can return something like a pointer to a value
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++)
  {
    // first param => store the Thread ID in here
    // second param => if you need to store some other attributes to the thread
    // third param => the runner function when the thread is in running
    // fourth param => argument of the runner routine
    // return 0 if the thread has been created successfully
    // here, the thread is created and running based on cpu time given
    if (pthread_create(&threads[i], NULL, increment_thread, NULL) != 0)
    {
      perror("Thread creation in ERROR");
      exit(EXIT_FAILURE);
    }
  }

  // joining makes sure that each thread has completed its routine, before the main thread
  // moves on to the next instructions
  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
  }

  printf("Final counter value: %d (Expected: %d)\n", counter, NUM_THREADS * INCREMENTS);

  return 0;
}

//! Bad result
//* Example output: Final counter value: 44967 (Expected: 100000)
//? why? Each thread is given a timeslice to run,
//? and if its timeslice expires or it blocks
//? (for example, while waiting on an I/O operation),
//? the scheduler will pause its execution and allow another thread to run.
//? This preemptive multitasking is why even if you join the threads later,
//? while they're running concurrently, the specific sequence of operations
//? (like reading, incrementing, and writing back the counter) can be
//? interrupted and interleaved with other threads.
//? That interleaving results in some threads stopping and waiting for CPU time,
//? and it’s precisely this lack of atomicity in the operations that causes the race condition.