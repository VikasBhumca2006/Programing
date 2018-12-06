#include "Memory_Manager.h"

int main ()
{
    char *p1 = NULL;
    char *p2 = NULL;
    char *p3 = NULL;
    mem_init();

    printf("\n\n\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);
    printf("\n\n");
    printf("Prnting Allocated List => ");
    print_List(headAllocList);


    printf("\n\n\n");
    p1 = (char *)alloc_mem(16);
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);


    printf("\n\n\n");
    p2 = (char *)alloc_mem(4);
    printf("Prnting Allocated List => ");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List => ");
    print_List(headAvailList);


    printf("\n\n\n");
    p3 = (char *)alloc_mem(20);
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

