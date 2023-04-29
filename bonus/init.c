#include "pipex_bonus.h"

static char	**get_env_path(char **env)
{
	char	**path;

	if (env == NULL)
		return (console_err("$\n", ERENV), NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			env[0][3] = '.';
			env[0][4] = ':';
			path = ft_split((*env) + 3, ':');
			if (path == NULL)
				return (console_err("$\n", ERHEAP), NULL);
			return (path);
		}
		env++;
	}
	return (console_err("$\n", ERPATH), NULL);
}

static int	*set_cmd_fdio(char *infile, char *outfile, int count)
{
	int	*fd;
	int	i;

	fd = (int *)malloc(sizeof(int) * count);
	if (fd == NULL)
		return (console_err("$\n", ERHEAP), NULL);
	i = 0;
	fd[i] = open(infile, O_RDONLY);
	if (fd[i++] == FAIL)
		return (perror("open"), free(fd), NULL);
	while (i < count)
	{
		if (pipe(fd + i) == FAIL)
			return (perror("pipe"), close_fds(fd, i), NULL);
		fd[i] = fd[i] ^ fd[i + 1];
		fd[i + 1] = fd[i] ^ fd[i + 1];
		fd[i] = fd[i] ^ fd[i + 1];
		i += 2;
	}
	fd[i] = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd[i] == FAIL)
		return (perror("open"), close_fds(fd, i), NULL);
	return (fd);
}

void	pipex_init(t_pipex *pipex, int count, char const **av, char **env)
{
	char	**path;
	
	path = get_env_path(env);
	if (path == NULL)
		exit(EXIT_FAILURE);
	pipex->cmd = parse_cmds(av + 1, count, (char const **)path);
	free_2d(path);
	if (pipex->cmd == NULL)
		exit(EXIT_FAILURE);
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * count);
	if (pipex->pid == NULL)
	{
		console_err("$\n", ERHEAP);
		release(pipex, CMDS | PROC_FAILURE);
	}
	pipex->count = count;
	set_cmd_fdio(pipex, av[0], av[count + 1]);
}