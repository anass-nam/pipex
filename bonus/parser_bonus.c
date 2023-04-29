#include "pipex_bonus.h"

static char	*get_cmd_fullpath(char const *basename, char const **path)
{
	char	*cmd;
	char	*cmd_fullpath;

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

t_cmd	**parse_cmds(char const **av, int count, char const **path)
{
	t_cmd	**cmds;
	int		i;

	cmds = (t_cmd **)malloc(sizeof(t_cmd *) * count);
	if (cmds == NULL)
		return (console_err("$\n", ERHEAP), NULL);
	while (i < count)
	{
		cmds[i] = parse_cmd(av[i], path);
		if (cmds[1] == NULL)
			return (free_cmds(cmds, i), NULL);
	}
	return (cmds);
}

