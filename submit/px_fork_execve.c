/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:11:06 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/01 19:11:06 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"

extern char	**environ;

char	*px_resolve_command_path(char *command);
char	*px_getenv_value(char *key);
char	*px_resolve_path(char **path, char *target);

int	px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2])
{
	int		cpid;
	char	*abs_path;

	abs_path = px_resolve_command_path(cmd);
	if (abs_path == NULL)
		return (-1);
	cpid = fork();
	if (cpid == 0)
	{
		dup2(pre_pipe[0], 0);
		dup2(now_pipe[1], 1);
		close(pre_pipe[0]);
		close(pre_pipe[1]);
		close(now_pipe[0]);
		close(now_pipe[1]);
		if (execve(abs_path, (char *[]){cmd, NULL}, environ) == -1)
		{
			write(1, "error\n", 6);
			exit(1);
		}
	}
	free(abs_path);
	return (cpid);
}

char	*px_resolve_command_path(char *command)
{
	char	*paths;
	char	**path_ary;
	char	*resolved;
	size_t	index;

	if (access(command, F_OK) == -1 && errno != ENOENT)
		return (NULL);
	paths = px_getenv_value("PATH");
	if (paths == NULL && errno != 0)
		return (NULL);
	else if (paths == NULL)
	{
		errno = ENOENT;
		return (free(paths), NULL);
	}
	path_ary = ft_split(paths, ':');
	free(paths);
	if (path_ary == NULL)
		return (NULL);
	resolved = px_resolve_path(path_ary, command);
	index = 0;
	while (path_ary[index] != NULL)
		free(path_ary[index++]);
	free(path_ary);
	return (resolved);
}

char	*px_resolve_path(char **path, char *target)
{
	char	*joined;
	char	*tmp;
	int		is_exists;

	while (*path != NULL)
	{
		tmp = ft_strjoin(*path, "/");
		if (tmp == NULL)
			return (NULL);
		joined = ft_strjoin(tmp, target);
		free(tmp);
		if (joined == NULL)
			return (NULL);
		is_exists = access(joined, F_OK);
		if (is_exists == 0)
			return (joined);
		free(joined);
		if (is_exists == -1 && errno != ENOENT)
			return (NULL);
		errno = 0;
		path++;
	}
	errno = ENOENT;
	return (NULL);
}

/**
 * @brief get value in memory from environ.environ(7)
 * @param key keyvalue
 */
char	*px_getenv_value(char *key)
{
	size_t	index;
	size_t	iter;

	index = 0;
	while (environ[index] != NULL)
	{
		if (ft_strncmp(key, environ[index], ft_strlen(key)) == 0)
			break ;
		index++;
	}
	if (environ[index] == NULL)
		return (NULL);
	iter = 0;
	while (environ[index][iter] != '=' && environ[index][iter] != '\0')
		iter++;
	if (environ[index][iter] == '\0')
		return (NULL);
	return (ft_strdup(environ[index] + iter + 1));
}
