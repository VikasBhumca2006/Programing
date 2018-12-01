#include <stdio.h>
#include <stdlib.h>

//#define NUMBER_OF_BYTE 40960    //40kb
#define NUMBER_OF_BYTE 116    //40kb
#define MIN_BLOCK_SIZE 4        //4 Byte

char mem_array[NUMBER_OF_BYTE]={0};

//int base = &mem_array[0];

struct _men_track {
        int index;    // Index of array from where memory is Available/free.
        int next;     // Index of next structure of Available/free list.
        int size;     // Size of block which is Available/free.
};

typedef struct _men_track sMemTrack;

sMemTrack *headAvailList;
sMemTrack *headAllocList;

void mem_init();
void free_mem(void *);
void *alloc_mem(int size);

void mem_init()
{
	headAvailList = (sMemTrack *)&mem_array[0];
	headAvailList->index = sizeof(sMemTrack);
	headAvailList->size = NUMBER_OF_BYTE - headAvailList->index ;
	headAvailList->next = -1;

	headAllocList = NULL;
}

void print_List (sMemTrack *List)
{
	sMemTrack *tmp = NULL;
	
	for (tmp = List; tmp; )
	{
		printf(" => {%d, %d, %d}",(tmp->index -12 ), tmp->size, tmp->next );

		if (tmp->next == -1)
			tmp = NULL;
		else
			tmp = (sMemTrack *)&mem_array[tmp->next];
	}
}

void *alloc_mem(int reqSize)
{
	sMemTrack *availTemp;
	sMemTrack *allocTemp;
	sMemTrack *temp;
	int curr, next, prev;

	int allocSize = (reqSize % MIN_BLOCK_SIZE == 0) ? reqSize : ((reqSize/MIN_BLOCK_SIZE + 1) * MIN_BLOCK_SIZE);

	/* 
	 * If requested memory is greater than the sum of requested 
 	 * and memory required to keep track of allocated memory 
	 */

	if (NUMBER_OF_BYTE - sizeof(sMemTrack) < allocSize)  //Need to check this condition
	{
		printf("Insufficient Memory\n");
		return NULL;
	}

	availTemp = headAvailList;
	prev = -1;
	
	/* Traverse the list of free blocks */
	/* Here we are using first fit for memory allocation */
	do
	{
		if (availTemp->size >= sizeof(sMemTrack) + allocSize)  //Need to change -> Aman
		{	
			allocTemp = availTemp;
			availTemp =  (sMemTrack *)&mem_array[availTemp->index + allocSize];
			availTemp->size = allocTemp->size - allocSize - sizeof(sMemTrack);
			allocTemp->size = allocSize;
			availTemp->index = allocTemp->index + allocSize + sizeof(sMemTrack);
			availTemp->next = allocTemp->next;	
			allocTemp->next = -1;

			if (NULL == headAllocList )
			{
				headAvailList = availTemp;
				headAllocList = allocTemp;
			}
			else
			{
				if ( headAvailList == allocTemp )
				{
					allocTemp->next = headAllocList->index - sizeof(sMemTrack);
					headAllocList = allocTemp;
					headAvailList = (sMemTrack *)&mem_array[availTemp->index - sizeof(sMemTrack)];
				}
				else 
				{
					temp = (sMemTrack *)&mem_array[prev];
					temp->next =  availTemp->index - sizeof(sMemTrack);
				}
			}

			return (void *)&mem_array[allocTemp->index];
		}
		/* No need to keep the track of left memory for which size of sMemTrack  is not left */
		else if (availTemp->size > allocSize)
		{
			allocTemp = availTemp;
			availTemp->next = allocTemp->next;
			allocTemp->next = headAllocList->index - sizeof(sMemTrack);
			headAvailList =  (sMemTrack *)&mem_array[allocTemp->index - sizeof(sMemTrack)];
			
			if ( NULL == headAllocList )
			{
				headAvailList = availTemp;
			}
			else
			{
				temp = (sMemTrack *)&mem_array[prev];
				temp->next =  availTemp->index - sizeof(sMemTrack);
			}
			return (void *)&mem_array[allocTemp->index];
		}
		else
		{
			prev = availTemp->index - sizeof(sMemTrack);
		}
	}while (next != -1);

	if (0 == next)
	{
		printf("Insufficient Memory\n");
		return NULL;
	}
}

void free_mem(void *ptr)
{
    sMemTrack *tempFree = NULL;
    sMemTrack *temp = NULL;
    int prev = -1, inBeg = 1;

    tempFree = (sMemTrack *)(((char *)ptr) - sizeof(sMemTrack));

    /* Here we are updating the list of allocated blocks Removed the blocks which one is freed.  */
    for (temp = headAllocList; temp; )
    {
        if ( temp->index ==  tempFree->index )
        {
            if ( headAllocList == temp )
            {
                if ( temp->next == -1 )
                    headAllocList = NULL;
                else
                    headAllocList = (sMemTrack *)&mem_array[tempFree->next];

                break;
            }
            else
            {
                ((sMemTrack *)&mem_array[prev])->next = tempFree->next;
            }
            break;
        }
        prev = temp->index - sizeof(sMemTrack);

        if (temp->next == -1)
            temp = NULL;
        else
            temp = (sMemTrack *)&mem_array[temp->next];
    }

    /* if all the blocks are allocated them one block is freed */
    if ( NULL == headAvailList )
    {
        headAvailList = tempFree;
        tempFree->next = -1;
        return;
    }

    /* Here we are updating the list of freed blocks Add the blocks which one is freed.  */
    prev = -1;
    inBeg = 1;
    for (temp = headAvailList; temp; )
    {
        /* Got the block whose next block is being freed.  Combine the block and freed block. */
        if (temp->index + temp->size == tempFree->index - sizeof(sMemTrack))
        {
            temp->size = temp->size + tempFree->size + sizeof(sMemTrack);
            inBeg = 0;
        }


        /* Got the block whose previous block is being freed.  */
        if (tempFree->index + tempFree->size == temp->index - sizeof(sMemTrack) )  // Added on 1 Dec 2018
        {
            /*
             * If we already combine the blocks in previous If case.
             * Means combined the block whose next block is being freed with free block.
             * Now se have a new block.
             * Then combine the new block with the block whose previous block is being freed.
             */ 
            if (inBeg == 0)
            {
                ((sMemTrack *)&mem_array[prev])->next = temp->next;
                ((sMemTrack *)&mem_array[prev])->size += temp->size + sizeof(sMemTrack);
                return;
            }
            /* Combine the block whose previous block is being freed with free block. */
            else
            {
                tempFree->size = tempFree->size + temp->size + sizeof(sMemTrack);
                tempFree->next = temp->next;

                if ( prev != -1 )
                {
                    ((sMemTrack *)&mem_array[prev])->next = tempFree->index - sizeof(sMemTrack);
                    return;
                }
                

            }
            inBeg = 0;
            break;
        }

        if ( temp->index > tempFree->index )
            break;

        prev = (temp->index - sizeof(sMemTrack));

        if (temp->next == -1)
            temp = NULL;
        else
            temp = (sMemTrack *)&mem_array[temp->next];

    }

    if ( prev == -1 )
    {
        headAvailList = tempFree;

        if ( inBeg )
            tempFree->next = temp->index - sizeof(sMemTrack);
    }
    else
    {
        temp = (sMemTrack *)&mem_array[prev];
        tempFree->next = temp->next;

        if ( inBeg )
            temp->next = tempFree->index - sizeof(sMemTrack);

    }
}


int main ()
{
    int *p1 = NULL;
    int *p2 = NULL;
    int *p3 = NULL;
    int *p4 = NULL;
    int *p5 = NULL;
    mem_init();

    printf("\n\n\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);


    printf("\n\n\n");
    p1 = alloc_mem(16);
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);


    printf("\n\n\n");
    p2 = alloc_mem(4);
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);


    printf("\n\n\n");
    p3 = alloc_mem(20);
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);


#ifdef FREE_P1    
    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#elif FREE_P2
    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#elif FREE_P3
    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#elif FREE_P12
    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

#elif FREE_P13
    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#elif FREE_P23
    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#elif FREE_P123
    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#elif FREE_P231
    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

#elif FREE_P312
    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

#elif FREE_P132
    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");

#elif FREE_P213
    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

#elif FREE_P321
    printf("\n\n\n");
    free_mem(p3);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p2);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);

    printf("\n\n\n");
    free_mem(p1);
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
#endif
}

