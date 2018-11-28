#include "Memory_Manager.h"

int main ()
{
        int *p1 = NULL;
        int *p2 = NULL;
        int *p3 = NULL;
        int *p4 = NULL;
        int *p5 = NULL;
        mem_init();

printf("\n\n\n");
    printf("Prnting Available List\n");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);


printf("\n\n\n");
        p1 = alloc_mem(1);
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List\n");
    print_List(headAvailList);


printf("\n\n\n");
        p2 = alloc_mem(5);
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List\n");
    print_List(headAvailList);

    
printf("\n\n\n");
        p3 = alloc_mem(8);
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);
    printf("\n");
    printf("Prnting Available List\n");
    print_List(headAvailList);



printf("\n\n\n");
        p4 = alloc_mem(1);
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);
    printf("Prnting Available List\n");
    print_List(headAvailList);



printf("\n\n\n");
        free_mem(p1);
    printf("Prnting Available List\n");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);

printf("\n\n\n");
        free_mem(p2);
    printf("Prnting Available List\n");
    print_List(headAvailList);
    printf("\n");
    printf("Prnting Allocated List List\n");
    print_List(headAllocList);
}


