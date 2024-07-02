/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipex_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:14:53 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 14:57:43 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "px_errors.h"
#include "px.h"
#include "px_types.h"

t_f_px_fork	px_return_fork_for_file(int index, int argc);

int	px_pipex_from_file(int argc, char *argv[])
{
	int			index;
	int			pre_fds[2];
	int			now_fds[2];
	t_f_px_fork	f_fork;

	if (pipe(pre_fds) == -1)
		return (-1);
	index = 1;
	while (index < argc)
	{
		if (pipe(now_fds) == -1)
			return (-1);
		f_fork = px_return_fork_for_file(index, argc);
		if (f_fork == NULL || f_fork(argv[index], pre_fds, now_fds) == -1 || px_close_pipe(pre_fds) == -1)
			return (-1);
		pre_fds[0] = now_fds[0];
		pre_fds[1] = now_fds[1];
		index++;
	}
	if (px_wait_termed(argc - 1) == -1 || px_close_pipe(pre_fds) == -1)
		return (-1);
	return (0);
}

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
