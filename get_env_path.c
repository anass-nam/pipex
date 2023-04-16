#include "pipex.h"


static char	**extract_path(char const *path)
{
	char	**paths;
	char	*tmp;

	tmp = (char *)path + 3;
	tmp[0] = '.';
	tmp[1] = ':';
	paths = ft_split(tmp, ':');
	if (paths == NULL)
		return (ft_putendl_fd(ERHEAP, STDERR_FILENO), NULL);
	return (paths);
}

char	**get_env_path(char const **env)
{
	char	**path;

	if (env == NULL)
		return (ft_putendl_fd(ERENV, STDERR_FILENO), NULL);
	path = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			path = extract_path(*env);
		env++;
	}
	if (path == NULL)
		ft_putendl_fd(ERPATH, STDERR_FILENO);
	return (path);
}

 