#include "Memory_Manager.h"

void mem_init()
{
    headAvailList = (sMemTrack *)&mem_array[0];
    headAvailList->index = sizeof(sMemTrack);
    headAvailList->size = NUMBER_OF_BYTE - headAvailList->index ;
    headAvailList->next = -1;

    headAllocList = NULL;
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
        //curr = availTemp->index - (sizeof(sMemTrack);
        //next = availTemp->next;

        //if (availTemp->size >=   sizeof(sMemTrack) + allocSize + MIN_BLOCK_SIZE)
        if (availTemp->size >= sizeof(sMemTrack) + allocSize)
        {   
            allocTemp = availTemp;
            availTemp =  (sMemTrack *)&mem_array[availTemp->index + allocSize];
            availTemp->size = allocTemp->size - allocSize - sizeof(sMemTrack);
            allocTemp->size = allocSize;
            availTemp->index = allocTemp->index + allocSize + sizeof(sMemTrack);
            availTemp->next = allocTemp->next;  
            allocTemp->next = -1;

            //if (&mem_array[allocTemp->index - sizeof(sMemTrack)] == headAvailList)
            if (NULL == headAllocList )
            {
                headAvailList = availTemp;
                headAllocList = allocTemp;
            }
            else
            {
                if ( headAvailList == allocTemp )
                {
                    allocTemp->next = headAllocList->next ;
                    headAllocList = allocTemp;
                    headAvailList = (sMemTrack *)&mem_array[allocTemp->index - sizeof(sMemTrack)];
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
            allocTemp->next = headAllocList->next ;
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
            //availTemp = (sMemTrack *)&mem_array[next];
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
    /* 
     * Here we are updating the list of allocated blocks 
     * Removed the blocks which one is freed.
     */
    for (temp = headAllocList; temp->next != -1; )
    {
        if ( temp == tempFree )
        {
            if ( headAllocList == temp )
                headAllocList->next = tempFree->next;
            else
            {
                ((sMemTrack *)&mem_array[prev])->next = tempFree->next;
            }
            break;
        }
        prev = temp->index - sizeof(sMemTrack);
        temp = (sMemTrack *)&mem_array[temp->next];
    }

    /* 
     * Here we are updating the list of freed blocks 
     * Add the blocks which one is freed.
     */
    prev = -1;
    for (temp = headAvailList; temp->next != -1; )
    {
        inBeg = 1;

               /*
                * Got the block whose next block is being freed.
                * Combine the block and freed block.
                */
        if (&mem_array[temp->index + temp->size] == tempFree)
        {
            temp->size = temp->size + tempFree->size + sizeof(sMemTrack);
            inBeg = 0;
        }


           /* 
            * Got the block whose previous block is being freed.
            */
        if (&mem_array[tempFree->index + tempFree->size] == &mem_array[temp->next]) 
        {
                       /*
                        * If we already combine the blocks in previous If case.
                        * Means combined the block whose next block is being freed with free block.
            * Now se have a new block.
                    * Then combine the new block with the block whose previous block is being freed.
                        */ 
            if (inBeg == 0)
            {
                temp->size = temp->size + ((sMemTrack *)&mem_array[temp->next])->size + sizeof(sMemTrack);
                temp->next = ((sMemTrack*)(&mem_array[tempFree->index + tempFree->size]))->next;
            }
            
                       /*
                        * Combine the block whose previous block is being freed with free block.
                        */
            else
            {
                tempFree->size = tempFree->size + ((sMemTrack *)&mem_array[temp->next])->size + sizeof(sMemTrack);
                tempFree->next = temp->next;
                ((sMemTrack *)&mem_array[prev])->next = tempFree->index - sizeof(sMemTrack);
            }
            inBeg = 0;
        }
        prev = (temp->index - sizeof(sMemTrack));
    }

    if (inBeg)
    {
        headAvailList = tempFree;
        tempFree->next = temp->next;
    }
}

void print_List (sMemTrack *List)
{
    sMemTrack *tmp = NULL;
    
    for (tmp = List; tmp; )
    {
        printf("Structure [i] index = %d\t size = %d\t next = %d\n",tmp->index, tmp->size, tmp->next);

        if (tmp->next == -1)
            tmp = NULL;
        else
            tmp = (sMemTrack *)&mem_array[tmp->next];
    }
}
