#include "pipex.h"

static char	*get_cmd_fullpath(char *basename, char const **path)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin("/", basename);
	if (isfailed(tmp == NULL, ERHEAP))
		return (NULL);
	while (*path)
	{
		tmp1 = ft_strjoin(*path, tmp);
		if (isfailed(tmp1 == NULL, ERHEAP))
			return (free(tmp), NULL);
		if (access(tmp1, F_OK | X_OK) == 0)
			return (free(tmp), tmp1);
		free(tmp1);
		path++;
	}
	free(tmp);
	ft_putstr_fd("pipex: \"", 2);
	ft_putstr_fd(basename, 2);
	ft_putendl_fd(ERINVC, 2);
	return (NULL);
}

static t_cmd	*parce_cmd(char const *fullcmd, char const **path)
{
	t_cmd	*cmd;
	char	**splited;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (isfailed(cmd == NULL, ERHEAP))
		return (NULL);
	splited = ft_split(fullcmd, ' ');
	if (isfailed(splited == NULL, ERHEAP))
		return (free(cmd), NULL);
	cmd->fullpath = get_cmd_fullpath(*splited, path);
	if (cmd->fullpath == NULL)
		return (free(cmd), free_2darr(splited), NULL);
	cmd->args = splited;
	return (cmd);
}

static t_cmd	**parce_cmds(int count, char const **cmds, char const **path)
{
	t_cmd	**cmd;
	int		i;

	cmd = (t_cmd **)malloc(sizeof(t_cmd *) * count);
	if (isfailed(cmd == NULL, ERHEAP))
		return (NULL);
	i = 0;
	while (i < count)
	{
		*(cmd + i) = parce_cmd(*(cmds + i), path);
		if (*(cmd + i) == NULL)
			return (free_cmds(cmd, i), NULL); // *
		i++;
	}
	return (cmd);
}

t_pipex	*parce_args(int count, char const **args, char const **path)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (isfailed(pipex == NULL, ERHEAP))
		return (NULL);
	pipex->infile = open(*args, O_RDONLY);
	isfailed(pipex->infile, "open");
	pipex->outfile = open(*(args + 3), O_RDWR | O_CREAT | O_TRUNC, 00644);
	isfailed(pipex->outfile, "open");
	pipex->cmd = parce_cmds(count, args + 1, path);
	return (pipex);
}

int main(int argc, char const **argv, char const **env)
{
	char **path = get_env_path(env);
	t_pipex *p = parce_args(argc - 3, argv + 1, (char const **)path);
	free_2darr(path);
	if (p->cmd)
		free_cmds(p->cmd, argc - 3);
	if (p->infile != -1)
		close(p->infile);
	if (p->outfile != -1)
		close(p->outfile);
	free(p);
	return 0;
}
