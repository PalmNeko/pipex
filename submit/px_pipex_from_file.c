/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipex_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:14:53 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/03 14:25:20 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "px_errors.h"
#include "px.h"
#include "px_types.h"

t_f_px_fork	px_return_fork_for_file(int index, int argc);
pid_t		px_pipe_for_file(int argc, char *argv[]);

int	px_pipex_from_file(int argc, char *argv[])
{
	int		exit_status;
	pid_t	last_pid;

	last_pid = px_pipe_for_file(argc, argv);
	if (last_pid == -1)
		return (-1);
	exit_status = px_wait_termed(argc - 1, last_pid);
	if (exit_status == -1)
		return (-1);
	return (exit_status);
}

pid_t	px_pipe_for_file(int argc, char *argv[])
{
	int			index;
	int			pre_fds[2];
	int			now_fds[2];
	pid_t		last_pid;
	pid_t		pid;

	if (pipe(pre_fds) == -1)
		return (-1);
	index = 1;
	last_pid = -1;
	while (index < argc)
	{
		if (pipe(now_fds) == -1)
			return (px_close_pipe(pre_fds), -1);
		pid = px_return_fork_for_file(index, argc)(
				argv[index], pre_fds, now_fds);
		if (index == argc - 2)
			last_pid = pid;
		if (pid == -1 || px_close_pipe(pre_fds) == -1)
			return (-1);
		ft_memmove(pre_fds, now_fds, sizeof(int) * 2);
		index++;
	}
	px_close_pipe(pre_fds);
	return (last_pid);
}

/**
 * @return NULL if occur error and set errno.
 * ERROR ERANGE out of function index
 */
t_f_px_fork	px_return_fork_for_file(int index, int argc)
{
	if (index == 1)
		return (px_fork_read);
	else if (index < argc - 1)
		return (px_fork_execve);
	else if (index == argc - 1)
		return (px_fork_write);
	else
		return (NULL);
}
