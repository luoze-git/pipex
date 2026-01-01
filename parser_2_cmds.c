#include "pipex.h"

int	find_path_idx_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	fetch_cmd_path(char *cmd_name, char **envp, char **path)
{
	int		idx;
	char	**dirs;
	char	*path_candidate;

	*path = NULL;
	idx = find_path_idx_envp(envp);
	if (idx == -1)
		return ;
	dirs = ft_split(envp[idx] + 5, ':');
	if (!dirs)
		fatal_parent_prefork("split dirs");
	idx = 0;
	while (dirs[idx])
	{
		path_candidate = ft_strjoin_3_safe(dirs[idx], "/", cmd_name);
		if (access(path_candidate, X_OK) == 0)
		{
			*path = path_candidate;
			break ;
		}
		free(path_candidate);
		idx++;
	}
	ft_free_split(dirs);
}

void	parse_cmd(char *cmd_str, t_cmd *cmd, char **envp)
{
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
		fatal_parent_prefork("split cmd argv");
	if (ft_strchr(cmd->argv[0], '/'))
	{
		cmd->path = ft_strdup(cmd->argv[0]);
		if (!cmd->path)
			fatal_parent_prefork("strdup cmd path");
	}
	else
		fetch_cmd_path(cmd->argv[0], envp, &(cmd->path));
}

void	parse_multi_cmds(t_parsed *p, char **argv, char **envp)
{
	int i;

	p->cmds = malloc(sizeof(t_cmd) * p->cmd_count);
	if (!p->cmds)
		fatal_parent_prefork("malloc cmds");
	i = 0;
	while (i < p->cmd_count)
	{
		parse_cmd(argv[p->cmd_start_idx + i], &p->cmds[i], envp);
		i++;
	}
}