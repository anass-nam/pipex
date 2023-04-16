#include "pipex.h"

static char	*get_cmd_fullpath(char *basename, char const **path)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin("/", basename);
	if (tmp == NULL)
		return (ft_putendl_fd(ERHEAP, STDERR_FILENO), NULL);
	while (*path)
	{
		tmp1 = ft_strjoin(*path, tmp);
		if (tmp1 == NULL)
			return (ft_putendl_fd(ERHEAP, STDERR_FILENO), free(tmp), NULL);
		if (access(tmp1, F_OK | X_OK) == 0)
			return (free(tmp), tmp1);
		free(tmp1);
		path++;
	}
	free(tmp);
	ft_putstr_fd("pipex: \"", STDERR_FILENO);
	ft_putstr_fd(basename, STDERR_FILENO);
	ft_putendl_fd(ERINVC, STDERR_FILENO);
	return (NULL);
}

static t_cmd	*parse_cmd(char const *fullcmd, char const **path)
{
	t_cmd	*cmd;
	char	**splited;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_putendl_fd(ERHEAP, STDERR_FILENO), NULL);
	splited = ft_split(fullcmd, ' ');
	if (splited == NULL)
		return (ft_putendl_fd(ERHEAP, STDERR_FILENO), free(cmd), NULL);
	cmd->fullpath = get_cmd_fullpath(*splited, path);
	if (cmd->fullpath == NULL)
		return (free(cmd), free_2darr(splited), NULL);
	cmd->args = splited;
	return (cmd);
}

static t_cmd	**parse_cmds(int count, char const **cmds, char const **path)
{
	t_cmd	**cmd;
	int		i;

	cmd = (t_cmd **)malloc(sizeof(t_cmd *) * count);
	if (cmd == NULL)
		return (ft_putendl_fd(ERHEAP, STDERR_FILENO), NULL);
	i = 0;
	while (i < count)
	{
		*(cmd + i) = parse_cmd(*(cmds + i), path);
		if (*(cmd + i) == NULL)
			return (free_cmds(cmd, i), NULL);
		i++;
	}
	return (cmd);
}

static t_pipex	*parse_args(int count, char const **args, char const **path)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (ft_putendl_fd(ERHEAP, STDERR_FILENO), NULL);
	pipex->infile = open(*args, O_RDONLY);
	if (pipex->infile == FAIL)
		return (perror("open"), free(pipex), NULL);
	pipex->outfile = open(*(args + 3), O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (pipex->outfile == FAIL)
	{
		close(pipex->infile);
		return (perror("open"), free(pipex), NULL);
	}
	pipex->cmd = parse_cmds(count, args + 1, path);
	if (pipex->cmd == NULL)
	{
		close(pipex->infile);
		close(pipex->outfile);
		return (free(pipex), NULL);
	}
	pipex->cmd_count = count;
	return (pipex);
}

t_pipex	*parcer(int argc, char const *argv[], char const **env)
{
	int		count;
	char	**path;
	t_pipex	*pipex;

	if (argc != 5)
		exit(EXIT_FAILURE);
	count = argc - 3;
	path = get_env_path(env);
	if (path == NULL)
		exit(EXIT_FAILURE);
	pipex = parse_args(count, argv + 1, (const char **)path);
	free_2darr(path);
	if (pipex == NULL)
		exit(EXIT_FAILURE);
	return (pipex);
}
