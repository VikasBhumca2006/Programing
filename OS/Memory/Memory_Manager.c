#include "Memory_Manager.h"

sMemTrack *headAvailList;
sMemTrack *headAllocList;

char *mem_alloc_array = NULL;


void mem_init()
{
	mem_alloc_array = (char *) malloc (NUMBER_OF_BYTE);

	if ( NULL == mem_alloc_array )
	{
	    printf("ERR:Memory Pool Allocation is failed");
	    exit(0);
	}


	headAvailList = (sMemTrack *)&mem_alloc_array[0];
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
			tmp = (sMemTrack *)&mem_alloc_array[tmp->next];
	}
}

void *alloc_mem(int reqSize)
{
	sMemTrack *availTemp;
	sMemTrack *allocTemp;
	sMemTrack *temp;
	int next = -1, prev;

	unsigned int allocSize = (reqSize % MIN_BLOCK_SIZE == 0) ? reqSize : ((reqSize/MIN_BLOCK_SIZE + 1) * MIN_BLOCK_SIZE);

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
			availTemp =  (sMemTrack *)&mem_alloc_array[availTemp->index + allocSize];
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
					headAvailList = (sMemTrack *)&mem_alloc_array[availTemp->index - sizeof(sMemTrack)];
				}
				else 
				{
					temp = (sMemTrack *)&mem_alloc_array[prev];
					temp->next =  availTemp->index - sizeof(sMemTrack);
				}
			}

			return (void *)&mem_alloc_array[allocTemp->index];
		}
		/* No need to keep the track of left memory for which size of sMemTrack  is not left */
		else if (availTemp->size > allocSize)
		{
			allocTemp = availTemp;
			availTemp->next = allocTemp->next;
			allocTemp->next = headAllocList->index - sizeof(sMemTrack);
			headAvailList =  (sMemTrack *)&mem_alloc_array[allocTemp->index - sizeof(sMemTrack)];
			
			if ( NULL == headAllocList )
			{
				headAvailList = availTemp;
			}
			else
			{
				temp = (sMemTrack *)&mem_alloc_array[prev];
				temp->next =  availTemp->index - sizeof(sMemTrack);
			}
			return (void *)&mem_alloc_array[allocTemp->index];
		}
		else
		{
			prev = availTemp->index - sizeof(sMemTrack);
		}
	}while (next != -1);

	if (0 == next)
	{
		printf("Insufficient Memory\n");
	}
		return NULL;
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
                    headAllocList = (sMemTrack *)&mem_alloc_array[tempFree->next];

                break;
            }
            else
            {
                ((sMemTrack *)&mem_alloc_array[prev])->next = tempFree->next;
            }
            break;
        }
        prev = temp->index - sizeof(sMemTrack);

        if (temp->next == -1)
            temp = NULL;
        else
            temp = (sMemTrack *)&mem_alloc_array[temp->next];
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
                ((sMemTrack *)&mem_alloc_array[prev])->next = temp->next;
                ((sMemTrack *)&mem_alloc_array[prev])->size += temp->size + sizeof(sMemTrack);
                return;
            }
            /* Combine the block whose previous block is being freed with free block. */
            else
            {
                tempFree->size = tempFree->size + temp->size + sizeof(sMemTrack);
                tempFree->next = temp->next;

                if ( prev != -1 )
                {
                    ((sMemTrack *)&mem_alloc_array[prev])->next = tempFree->index - sizeof(sMemTrack);
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
            temp = (sMemTrack *)&mem_alloc_array[temp->next];

    }

    if ( prev == -1 )
    {
        headAvailList = tempFree;

        if ( inBeg )
            tempFree->next = temp->index - sizeof(sMemTrack);
    }
    else
    {
        temp = (sMemTrack *)&mem_alloc_array[prev];
        tempFree->next = temp->next;

        if ( inBeg )
            temp->next = tempFree->index - sizeof(sMemTrack);

    }
}

#ifdef DEBUG_MEM_MGR

#endif
