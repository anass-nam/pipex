#include "pipex_bonus.h"

void	console_err(char *err_holder, ...)
{
	va_list	args;
	int		i;

	i = 0;
	if (err_holder)
	{
		va_start(args, err_holder);
		while (*(err_holder + i))
		{
			if (*(err_holder + i) == '$')
				ft_putstr_fd(va_arg(args, char *), STDERR_FILENO);
			else
				ft_putchar_fd(*(err_holder + i), STDERR_FILENO);
			i++;
		}
		va_end(args);
	}
}

void	free_2d(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_cmds(t_cmd **cmd, int i)
{
	while (i--)
	{
		free(cmd[i]->fullpath);
		cmd[i]->fullpath = NULL;
		free_2d(cmd[i]->args);
		free(cmd[i]);
		cmd[i] = NULL;
	}
	free(cmd);
	cmd = NULL;
}

void	close_fds(int *fd, int i)
{
	while (i--)
		close(fd[i]);
	free(fd);
	fd == NULL;
	
}

void	release(t_pipex *pipex, t_byte option)
{
	if (option & INFILE)
		close(pipex->fd[0]);
	if (option & OUTFILE)
		close(pipex->fd[(pipex->count * 2) - 1]);
	if (option & FDS)
		close_fds(pipex->fd, pipex->count * 2);
	if (option & PIDS)
		free(pipex->pid);
	if (option & CMDS)
		free_cmds(pipex->cmd, pipex->count);
	if (option & PROC_SUCCESS)
		exit(EXIT_SUCCESS);
	if (option & PROC_FAILURE)
		exit(EXIT_FAILURE);
}
