/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_resolve_command_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:48:57 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 16:50:39 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "px.h"
#include "libft.h"

char	*px_resolve_path_str(char *path_str, char *target);
char	*px_resolve_path(char **path, char *target);

char	*px_resolve_command_path(char *command)
{
	char	*paths;
	char	*resolved;

	if (command == NULL)
		return (ft_set_errno(ENOENT), NULL);
	else if (ft_strmatch("^./", command) || ft_strmatch("^/", command))
		return (ft_strdup(command));
	if (access(command, F_OK) == -1 && errno != ENOENT)
		return (NULL);
	paths = ft_getenv_value("PATH");
	if (paths == NULL && errno != 0)
		return (NULL);
	else if (paths == NULL)
		return (ft_set_errno(ENOENT), free(paths), NULL);
	resolved = px_resolve_path_str(paths, command);
	free(paths);
	return (resolved);
}

char	*px_resolve_path_str(char *path_str, char *target)
{
	size_t	index;
	char	*resolved;
	char	**path_ary;

	path_ary = ft_split(path_str, ':');
	if (path_ary == NULL)
		return (NULL);
	resolved = px_resolve_path(path_ary, target);
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
