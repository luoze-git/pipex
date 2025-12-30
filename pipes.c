
#include "pipex.h"

int	**setup_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		fatal_parent_prefork("malloc pipes");
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			fatal_parent_prefork("pipe");
		i++;
	}
	return (pipes);
}
