#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

void *Print_Odd_Number();
void *Print_Even_Number();
int count = 0;
#define COUNT_DONE 200


// Print odd numbers
void *Print_Odd_Number()
{
    for(;;)
    {
        // Lock mutex and then wait for signal to relase mutex
        pthread_mutex_lock( &count_mutex );

        if ( count % 2 != 0 )
        {
            pthread_cond_wait( &condition_var, &count_mutex );
        }

        count++;
        printf("Counter value Print_Odd_Number: %d\n",count);
        pthread_cond_signal( &condition_var );

        if ( count >= COUNT_DONE )
        {
            pthread_mutex_unlock( &count_mutex );
            return(NULL);
        }

        pthread_mutex_unlock( &count_mutex );
    }
}

// print even numbers
void *Print_Even_Number()
{
    for(;;)
    {
        // Lock mutex and then wait for signal to relase mutex
        pthread_mutex_lock( &count_mutex );

        if ( count % 2 == 0 )
        {
            pthread_cond_wait( &condition_var, &count_mutex );
        }

        count++;
        printf("Counter value Print_Even_Number: %d\n",count);
        pthread_cond_signal( &condition_var );

        if( count >= COUNT_DONE )
        {
            pthread_mutex_unlock( &count_mutex );
            return(NULL);
        }

        pthread_mutex_unlock( &count_mutex );
    }
}

int main()
{
    pthread_t thread1, thread2;

    pthread_create( &thread1, NULL, &Print_Odd_Number, NULL);
    pthread_create( &thread2, NULL, &Print_Even_Number, NULL);

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    exit(0);
    return 0;
}
