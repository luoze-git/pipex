#include "pipex.h"

// name file1 cmd1 cmd2 file2
// 0     1     2    3    4

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

	idx = find_path_idx_envp(envp);
	if (idx == -1)
		fatal_parent_prefork("no PATH in envp");
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
			break;
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
		fatal_parent_prefork("parse cmd argv");
	if (ft_strchr(cmd->argv[0], '/'))
	{
		cmd->path = ft_strdup(cmd->argv[0]);
		if (!cmd->path)
			fatal_parent_prefork("strdup cmd path");
	}
	else
		fetch_cmd_path(cmd->argv[0], envp, &(cmd->path));
}

t_parsed	*parse_input(int argc, char **argv, char **envp)
{
	t_parsed	*parsed;
	int			cmd_i;

	parsed = malloc(sizeof(t_parsed));
	if (!parsed)
		fatal_parent_prefork("malloc parsed");
	parsed->in_fd = open(argv[1], O_RDONLY);
	if (parsed->in_fd < 0)
		fatal_parent_prefork(argv[1]);
	cmd_i = 0;
	parsed->cmd_count = argc - 3;
	parsed->cmds = malloc(sizeof(t_cmd) * parsed->cmd_count);
	if (!parsed->cmds)
		fatal_parent_prefork("malloc cmds");
	while (cmd_i < argc - 3)
	{
		parse_cmd(argv[cmd_i + 2], &parsed->cmds[cmd_i], envp);
		cmd_i++;
	}
	parsed->out_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (parsed->out_fd < 0)
		fatal_parent_prefork(argv[argc - 1]);
	return (parsed);
}
