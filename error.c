#include "pipex.h"

void fatal_child(char* msg)
{
    perror(msg);
    exit(1);
}
