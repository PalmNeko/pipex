// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   px_fork_execve.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/01 19:11:06 by tookuyam          #+#    #+#             */
// /*   Updated: 2024/07/01 19:11:06 by tookuyam         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <sys/types.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <errno.h>
// #include <stdbool.h>
// #include "px.h"
// #include "libft.h"

// char	*px_resolve_command_path(char *command);
// char	*px_resolve_path_str(char *path_str, char *target);
// char	*px_resolve_path(char **path, char *target);
// void	free_termed_null(char **mems);
// bool	px_is_permission_error(int eno);
// bool	px_is_not_exists(int eno);
// int		px_on_fork_execve(char *abs_path, char **arguments, int pre_pipe[2], int now_pipe[2]);

// pid_t	px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2])
// {
// 	pid_t		cpid;
// 	char		*abs_path;
// 	char		**arguments;
// 	int			exit_stat;

// 	arguments = ft_split(cmd, ' ');
// 	if (arguments == NULL)
// 		return (-1);
// 	abs_path = px_resolve_command_path(arguments[0]);
// 	if (abs_path == NULL && errno != ENOENT)
// 		return (px_perrinfo(arguments[0]), free_termed_null(arguments), -1);
// 	cpid = fork();
// 	if (cpid == 0)
// 	{
// 		exit_stat = px_on_fork_execve(abs_path, arguments, pre_pipe, now_pipe);
// 		if (exit_stat == 127)
// 			px_perror_cmd_not_found(arguments[0]);
// 		else
// 			px_perrinfo(arguments[0]);
// 	}
// 	if (cpid == 0)
// 		exit(exit_stat);
// 	free_termed_null(arguments);
// 	free(abs_path);
// 	return (cpid);
// }

// /**
//  * success: not returned because call execve.
//  * return 127: command not found
//  * return 126: permission error
//  * return 125: some error
//  */
// int	px_on_fork_execve(char *abs_path, char **arguments, int pre_pipe[2], int now_pipe[2])
// {
// 	extern char	**environ;

// 	if (abs_path == NULL)
// 		return (127);
// 	dup2(pre_pipe[0], 0);
// 	dup2(now_pipe[1], 1);
// 	px_close_pipe(pre_pipe);
// 	px_close_pipe(now_pipe);
// 	execve(abs_path, arguments, environ);
// 	if (px_is_not_exists(errno))
// 		return (127);
// 	else if (px_is_permission_error(errno))
// 		return (126);
// 	else
// 		return (125);
// }
