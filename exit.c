# include "pipex.h"

void	error_exit(void)
{
	perror("pipex");
	exit(1);
}
