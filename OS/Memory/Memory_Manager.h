#ifndef MEMORY_MANAGER_HEADER_FILE_H
#define MEMORY_MANAGER_HEADER_FILE_H

#include <stdio.h>
#include <stdlib.h>
//#define NUMBER_OF_BYTE 40960    //40kb
#define NUMBER_OF_BYTE 40960    //40kb
#define MIN_BLOCK_SIZE 4        //4 Byte

struct _men_track {
        unsigned int index;    // Index of array from where memory is Available/free.
        unsigned int size;     // Size of block which is Available/free.
        int next;     // Index of next structure of Available/free list.
};

typedef struct _men_track sMemTrack;

extern sMemTrack *headAvailList;
extern sMemTrack *headAllocList;

//char *mem_alloc_array = NULL;

void mem_init();
void free_mem(void *);
void *alloc_mem(int size);
void print_List (sMemTrack *List);

#endif
