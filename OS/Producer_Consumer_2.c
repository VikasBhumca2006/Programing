# include <stdio.h>
# include <pthread.h>


# define BufferSize 10

int BufferIndex=0;
char *BUFFER;

pthread_cond_t condp    =   PTHREAD_COND_INITIALIZER;
pthread_cond_t condc    =   PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar    =   PTHREAD_MUTEX_INITIALIZER;


void *Producer()
{
    for(;;)
    {
        pthread_mutex_lock(&mVar);

        if(BufferIndex==BufferSize)
        {
            pthread_cond_wait(&condp,&mVar);
        }

        BUFFER[BufferIndex++]='@';

        printf("Produce : %d \n",BufferIndex);

        pthread_cond_signal(&condc);

        pthread_mutex_unlock(&mVar);
    }

}

void *Consumer()
{
    for(;;)
    {
        pthread_mutex_lock(&mVar);

        if(BufferIndex==-1)
        {
            pthread_cond_wait(&condc,&mVar);
        }

        printf("Consume : %d \n",BufferIndex--);

        pthread_cond_signal(&condp);

        pthread_mutex_unlock(&mVar);
    }
}

int main()
{
    pthread_t ptid,ctid;

    BUFFER=(char *) malloc(sizeof(char) * BufferSize);
    if ( NULL == BUFFER )
    {
        return 0;
    }

    pthread_create(&ptid,NULL,Producer,NULL);
    pthread_create(&ctid,NULL,Consumer,NULL);

    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);

    return 0;
}
