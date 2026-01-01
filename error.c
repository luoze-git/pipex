#include "pipex.h"

void	fatal_child(t_parent *parent, char *msg, int exit_code)
{
	perror(msg);
	close_all_fd_safe(parent);
	cleanup_child(parent);
	exit(exit_code);
}

void	fatal_parent_prefork(const char *msg_where)
{
	perror(msg_where);
	exit(1);
}

/*exit_code is 1. Children are waited for only to avoid zombies*/
void	fatal_parent_postfork(t_parent *parent, const char *msg_where)
{
	perror(msg_where);
	close_all_fd_safe(parent);
	parent_wait_and_collect(parent);
	exit(1);
}
