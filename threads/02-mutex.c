#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define INCREMENTS 10000

int counter = 0;
pthread_mutex_t counter_mutex; // This will protect the counter from race conditions

void *increment_thread(void *arg)
{
  for (int i = 0; i < INCREMENTS; i++)
  {
    // lock the global variable
    pthread_mutex_lock(&counter_mutex);
    counter++;

    // unlock the global variable
    pthread_mutex_unlock(&counter_mutex);
  }

  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];

  // init the mutex - An uninitialized mutex does not have valid internal state,
  // meaning that any attempt to lock or unlock it is undefined behavior.
  // NULL => default attributes for the mutex
  if (pthread_mutex_init(&counter_mutex, NULL) != 0)
  {
    perror("Mutex creation in ERROR");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_create(&threads[i], NULL, increment_thread, NULL) != 0)
    {
      perror("Thread creation in ERROR");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
  }

  printf("Final counter value: %d (Expected: %d)\n", counter, NUM_THREADS * INCREMENTS);

  // good practice, resource leak avoided,
  pthread_mutex_destroy(&counter_mutex);

  return 0;
}

//! Good result:
//* Example output: Final counter value: 100000 (Expected: 100000)
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