#include "Logger_Utility.h"

int fd;

void logger_init()
{
    fd = open("Debug_Log.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) 
    {
        perror("open failed");
    }

    if (dup2(fd, 1) == -1) 
    {
        perror("dup2 failed"); 
    }
}
