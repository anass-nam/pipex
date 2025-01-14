#include "pipex.h"

static char	*get_cmd_fullpath(char const *basename, char const **path)
{
	char	*cmd;
	char	*cmd_fullpath;

	if (*basename == '/' && access(basename, F_OK | X_OK) == -1)
		return (perror("access"), NULL);
	else if (*basename == '/')
		return (ft_strdup(basename));
	cmd = ft_strjoin("/", basename);
	if (cmd == NULL)
		return (console_err("$\n", ERHEAP), NULL);
	while (*path)
	{
		cmd_fullpath = ft_strjoin(*path, cmd);
		if (cmd_fullpath == NULL)
			return (console_err("$\n", ERHEAP), free(cmd), NULL);
		if (access(cmd_fullpath, F_OK | X_OK) == 0)
			return (free(cmd), cmd_fullpath);
		free(cmd_fullpath);
		path++;
	}
	free(cmd);
	console_err("pipex : $ : command not found\n", basename);
	return (NULL);
}

static t_cmd	*parse_cmd(const char *av, const char **path)
{
	t_cmd	*cmd;

	if (*av == '\0')
		return (console_err("$\n$\n", EREMPT, USAGE), NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (console_err("$\n", ERHEAP), NULL);
	cmd->args = ft_split(av, ' ');
	if (cmd->args == NULL)
		return (console_err("$\n", ERHEAP), free(cmd), NULL);
	cmd->fullpath = get_cmd_fullpath(cmd->args[0], path);
	if (cmd->fullpath == NULL)
		return (free_2d(cmd->args), free(cmd), NULL);
	return (cmd);
}

t_cmd	**parse_cmds(char const **av, char const **path)
{
	t_cmd	**cmds;

	cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 2);
	if (cmds == NULL)
		return (console_err("$\n", ERHEAP), NULL);
	cmds[0] = parse_cmd(av[0], path);
	if (cmds[0] == NULL)
		return (free(cmds), NULL);
	cmds[1] = parse_cmd(av[1], path);
	if (cmds[1] == NULL)
		return (free_cmds(cmds, 1), NULL);
	return (cmds);
}
