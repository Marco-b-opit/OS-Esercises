#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define INCREMENTS 10000

int counter = 0;
pthread_mutex_t mutex1, mutex2;

void *thread_a_routine(void *arg)
{
  for (int i = 0; i < INCREMENTS; i++)
  {
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
    counter++;
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
  }

  pthread_exit(NULL);
}

void *thread_b_routine(void *arg)
{
  for (int i = 0; i < INCREMENTS; i++)
  {
    pthread_mutex_lock(&mutex2);
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
  }

  pthread_exit(NULL);
}

int main()
{
  pthread_t threadA, threadB;

  if (pthread_mutex_init(&mutex1, NULL) != 0 || pthread_mutex_init(&mutex2, NULL) != 0)
  {
    perror("Error during mutex init");
    exit(EXIT_FAILURE);
  }

  if (pthread_create(&threadA, NULL, thread_a_routine, NULL) != 0)
  {
    perror("Error during thread A creation");
    exit(EXIT_FAILURE);
  }

  if (pthread_create(&threadB, NULL, thread_b_routine, NULL) != 0)
  {
    perror("Error during thread B creation");
    exit(EXIT_FAILURE);
  }

  pthread_join(threadA, NULL);
  pthread_join(threadB, NULL);

  printf("Final counter value: %d (expected value if no deadlock occurred: %d)\n",
         counter, 2 * INCREMENTS);

  pthread_mutex_destroy(&mutex1);
  pthread_mutex_destroy(&mutex2);

  return 0;
}

//* sometimes it might work because the task is relatively small
// but there's high risk of deadlock in here