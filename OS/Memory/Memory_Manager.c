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
	int next , prev, curr;
	void *retPtr = NULL;

#ifdef DEBUG_MEM_MGR
	printf ("\n\n  %s Allocated",__func__);
	print_List(headAllocList);
	printf ("\n  %s FreedList",__func__);
	print_List(headAvailList);
#endif

	unsigned int allocSize = (reqSize % MIN_BLOCK_SIZE == 0) ? reqSize : ((reqSize/MIN_BLOCK_SIZE + 1) * MIN_BLOCK_SIZE);

	/* 
	 * If requested memory is greater than the sum of requested 
	 * and memory required to keep track of allocated memory 
	 */

	if ( (NUMBER_OF_BYTE - sizeof(sMemTrack) < allocSize) ||
			(NULL == headAvailList))//Need to check this condition
	{
		printf("Insufficient Memory\n");
		retPtr = NULL;
		goto _return;
	}

	availTemp = headAvailList;
	prev = -1;

	/* Traverse the list of free blocks */
	/* Here we are using first fit for memory allocation */
	do
	{
		curr = availTemp->index - sizeof(sMemTrack);
		next = availTemp->next;

		if (availTemp->size >= sizeof(sMemTrack) + allocSize)
		{	
			allocTemp = availTemp;
			availTemp =  (sMemTrack *)&mem_alloc_array[availTemp->index + allocSize];
			availTemp->size = allocTemp->size - allocSize - sizeof(sMemTrack);
			allocTemp->size = allocSize;
			availTemp->index = allocTemp->index + allocSize + sizeof(sMemTrack);
			availTemp->next = allocTemp->next;	
			allocTemp->next = -1;

			/* First block is allocated from Memory Pool */
			if (NULL == headAllocList )
			{
				headAllocList = allocTemp;  
				/* If Memory is allocated first time from pool then 
				 * in free list there will not be any previous node. */
				headAvailList = availTemp;
			}
			else
			{
				/* Memory is allocated from first block of free list. */
				if ( headAvailList == allocTemp )
					//if ( headAvailList == availTemp )
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

			retPtr = (void *)&mem_alloc_array[allocTemp->index];
			goto _return;
		}
		/* No need to keep the track of left memory for which size of sMemTrack  is not left */
		else if (availTemp->size >= allocSize)  // Not completly fixed 
		{
			allocTemp = availTemp;

			/* First block is allocated from Memory Pool */
			if ( NULL == headAllocList ) /* This should never go in this if condition */
			{
				headAllocList = allocTemp;
				allocTemp->next = -1;
				/* If Memory is allocated first time from pool then 
				 * in free list there will not be any previous node. */
				headAvailList = availTemp;
			}
			else
			{
				/* First block from the free list is allocated. */
				if ( headAvailList == allocTemp )
				{
					/* This is not the last block of free list */
					if ( headAvailList->next != -1 )
					{
						headAvailList = (sMemTrack *)&mem_alloc_array[availTemp->next];
					}
					else /* Only one block was left which is alloced */
					{
						headAvailList = NULL;
					}

					allocTemp->next = headAllocList->index - sizeof(sMemTrack);
					headAllocList = allocTemp;
				}
				else
				{
					temp = (sMemTrack *)&mem_alloc_array[prev];
					temp->next =  availTemp->index - sizeof(sMemTrack);
				}
			}
			retPtr = (void *)&mem_alloc_array[allocTemp->index];
			goto _return;
		}
		else
		{
			prev = availTemp->index - sizeof(sMemTrack);
		}

		availTemp = (sMemTrack *)&mem_alloc_array[next];

	}while (next != -1);

	if (0 == next)
	{
		printf("Insufficient Memory\n");
	}
	retPtr = NULL;
	goto _return;

_return:
#ifdef DEBUG_MEM_MGR
	printf ("\n\n  %s Allocated",__func__);
	print_List(headAllocList);
	printf ("\n  %s FreedList",__func__);
	print_List(headAvailList);
#endif
	return retPtr;

}

void free_mem(void *ptr)
{

#ifdef DEBUG_MEM_MGR
	printf ("\n\n  %s Allocated",__func__);
	print_List(headAllocList);
	printf ("\n  %s FreedList",__func__);
	print_List(headAvailList);
#endif

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

