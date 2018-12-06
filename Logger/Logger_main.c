#include "Logger_Utility.h"

int main(int argc, char *argv[])
{
    int i = 0;
    logger_init();

    for (i = 1; i < argc; ++i) 
	printf (" argv[%d] = [%s]\n",i, argv[i]); 

}
