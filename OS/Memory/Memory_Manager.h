#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_BYTE 40960    //40kb
#define MIN_BLOCK_SIZE 4        //4 Byte

char mem_array[NUMBER_OF_BYTE]={0};

//int base = &mem_array[0];

struct _men_track {
        int index;    // Index of array from where memory is Available/free.
        int size;     // Size of block which is Available/free.
        int next;     // Index of next structure of Available/free list.
};

typedef struct _men_track sMemTrack;

sMemTrack *headAvailList;
sMemTrack *headAllocList;

void mem_init();
void free_mem(void *);
void *alloc_mem(int size);
void print_List (sMemTrack *List);
