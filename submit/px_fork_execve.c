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

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include "px.h"
#include "libft.h"

char	*px_resolve_command_path(char *command);
char	*px_resolve_path_str(char *path_str, char *target);
char	*px_resolve_path(char **path, char *target);
void	free_termed_null(char **mems);
bool	px_is_permission_error(int eno);
bool	px_is_not_exists(int eno);
int		px_on_fork_execve(char *abs_path, char **arguments, int pre_pipe[2], int now_pipe[2]);

pid_t	px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2])
{
	pid_t		cpid;
	char		*abs_path;
	char		**arguments;
	int			exit_stat;

	arguments = ft_split(cmd, ' ');
	if (arguments == NULL)
		return (-1);
	abs_path = px_resolve_command_path(arguments[0]);
	if (abs_path == NULL && errno != ENOENT)
		return (px_perrinfo(arguments[0]), free_termed_null(arguments), -1);
	cpid = fork();
	if (cpid == 0)
	{
		exit_stat = px_on_fork_execve(abs_path, arguments, pre_pipe, now_pipe);
		if (exit_stat == 127)
			px_perror_cmd_not_found(arguments[0]);
		else
			px_perrinfo(arguments[0]);
	}
	if (cpid == 0)
		exit(exit_stat);
	free_termed_null(arguments);
	free(abs_path);
	return (cpid);
}

/**
 * success: not returned because call execve.
 * return 127: command not found
 * return 126: permission error
 * return 125: some error
 */
int	px_on_fork_execve(char *abs_path, char **arguments, int pre_pipe[2], int now_pipe[2])
{
	extern char	**environ;

	if (abs_path == NULL)
		return (127);
	dup2(pre_pipe[0], 0);
	dup2(now_pipe[1], 1);
	px_close_pipe(pre_pipe);
	px_close_pipe(now_pipe);
	execve(abs_path, arguments, environ);
	if (px_is_not_exists(errno))
		return (127);
	else if (px_is_permission_error(errno))
		return (126);
	else
		return (125);
}

bool	px_is_permission_error(int eno)
{
	if (eno == EACCES
		|| eno == EISDIR
		|| eno == EPERM)
		return (true);
	else
		return (false);
}

bool	px_is_not_exists(int eno)
{
	if (eno == ENOENT)
		return (true);
	else
		return (false);
}

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

void	free_termed_null(char **mems)
{
	char	**iter;

	iter = mems;
	while (*iter != NULL)
	{
		free(*iter);
		iter++;
	}
	free(mems);
}
