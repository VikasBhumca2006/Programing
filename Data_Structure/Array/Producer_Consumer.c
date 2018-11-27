/*
   Solution to Thread_Producer Thread_Consumer Problem Using Ptheads, a mutex and condition
   variables         From Tanenbaum, Modern Operating Systems, 3rd Ed.

   In this version the buffer is a single number. The Thread_Producer is putting numbers
   into the shared buffer (in this case sequentially) And the Thread_Consumer is taking
   them out.If the buffer contains zero, that indicates that the buffer is empty.
   Any other value is valid.
   */

#include <stdio.h>
#include <pthread.h>

#define MAX 100000                      /* Numbers to produce */

pthread_mutex_t mVar    =   PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condp    =   PTHREAD_COND_INITIALIZER;
pthread_cond_t condc    =   PTHREAD_COND_INITIALIZER;

int buffer = 0;

void* Thread_Producer(void *ptr)
{
    int i;
    for (i = 1; i <= MAX; i++)
    {
        pthread_mutex_lock(&mVar);   /* protect buffer */

        while (buffer != 0)                        /* If there is something in the buffer then wait */
            pthread_cond_wait(&condp, &mVar);

        buffer = i;

        pthread_cond_signal(&condc);        /* wake up Thread_Consumer */

        pthread_mutex_unlock(&mVar);   /* release the buffer */
    }

    pthread_exit(0);
}

void* Thread_Consumer(void *ptr)
{
    int i;
    for (i = 1; i <= MAX; i++)
    {
        pthread_mutex_lock(&mVar); /* protect buffer */

        while (buffer == 0)                 /* If there is nothing in the buffer then wait */
            pthread_cond_wait(&condc, &mVar);

        buffer = 0;

        pthread_cond_signal(&condp);   /* wake up Thread_Consumer */

        pthread_mutex_unlock(&mVar);  /* release the buffer */
    }

    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t pro, con;

    // Initialize the mutex and condition variables
    /* What's the NULL for ??? */
    pthread_mutex_init(&mVar, NULL);
    pthread_cond_init(&condc, NULL);          /* Initialize Thread_Consumer condition variable */
    pthread_cond_init(&condp, NULL);                /* Initialize Thread_Producer condition variable */

    // Create the threads
    pthread_create(&con, NULL, Thread_Consumer, NULL);
    pthread_create(&pro, NULL, Thread_Producer, NULL);

    // Wait for the threads to finish Otherwise main might run to the end
    // and kill the entire process when it exits.
    pthread_join(con, NULL);
    pthread_join(pro, NULL);


    // Cleanup -- would happen automatically at end of program

    pthread_mutex_destroy(&mVar);      /* Free up mVar */
    pthread_cond_destroy(&condc);           /* Free up Thread_Consumer condition variable */
    pthread_cond_destroy(&condp);           /* Free up Thread_Producer condition variable */

}

