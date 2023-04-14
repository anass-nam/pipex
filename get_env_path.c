#include "pipex.h"


static char	**extract_path(char const *path)
{
	char	**paths;
	char	*tmp;

	tmp = (char *)path + 3;
	tmp[0] = '.';
	tmp[1] = ':';
	paths = ft_split(tmp, ':');
	if (isfailed(paths == NULL, ERHEAP))
		return (NULL);
	return (paths);
}

char	**get_env_path(char const **env)
{
	char	**path;

	if (isfailed(env == NULL, ERENV))
		return (NULL);
	path = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			path = extract_path(*env);
		env++;
	}
	isfailed(path == NULL, ERPATH);
	return (path);
}

 