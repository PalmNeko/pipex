/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipex_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:13:43 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 18:41:02 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "px_errors.h"
#include "px.h"
#include "px_types.h"

t_f_px_fork	px_return_fork_for_here_doc(int index, int argc);

int	px_pipex_here_doc(int argc, char *argv[])
{
	int			index;
	int			pre_fds[2];
	int			now_fds[2];
	t_f_px_fork	f_fork;

	if (argc < 6)
		return (PX_EARGCNT);
	if (pipe(pre_fds) == -1)
		return (-1);
	index = 2;
	while (index < argc)
	{
		if (pipe(now_fds) == -1)
			return (-1);
		f_fork = px_return_fork_for_here_doc(index, argc);
		if (f_fork == NULL || f_fork(argv[index], pre_fds, now_fds) == -1 || px_close_pipe(pre_fds) == -1)
			return (-1);
		ft_memmove(pre_fds, now_fds, sizeof(int) * 2);
		index++;
	}
	if (px_wait_termed(argc - 1) == -1 || px_close_pipe(pre_fds) == -1)
		return (-1);
	return (0);
}

/**
 * @return NULL if occur error and set errno.
 * ERROR ERANGE out of function index
 */
t_f_px_fork	px_return_fork_for_here_doc(int index, int argc)
{
	if (index == 2)
		return (px_fork_here_doc);
	else if (index < argc - 1)
		return (px_fork_execve);
	else if (index == argc - 1)
		return (px_fork_write);
	else
	{
		errno = ERANGE;
		return (NULL);
	}
}
