#include <stdio.h>
#include <stdlib.h>

typedef void (*funPtr)();

funPtr *Outer2_Function ()
{
    int start = 0;
    printf ("\nIn Outer2_Function Start = [%p]", &start);
    void Inner2_Function ()
    {
        printf ("\nIn Inner2_Function [%p]", Inner2_Function);
    }
    printf ("\nOuter2_Function Inner2_Function [%p]", Inner2_Function);
    int end = 0;
    printf ("\nIn Outer2_Function End = [%p]", &end);

    return Inner2_Function;
}
funPtr *Outer_Function ()
{
    int start = 0;
    printf ("\nIn Outer_Function Start = [%p]", &start);
    void Inner_Function ()
    {
        printf ("\nIn Inner_Function [%p]", Inner_Function);
    }
    printf ("\nOuter_Function Inner_Function [%p]", Inner_Function);
    int end = 0;
    printf ("\nIn Outer_Function End = [%p]", &end);

    return Inner_Function;
}


int main ()
{
    funPtr ptrFun = Outer_Function();
    Outer2_Function();
    //printf ("\nIn Inner_Function [%p]", ptrFun);
    //printf ("\n\n\n");
    ptrFun();
}

