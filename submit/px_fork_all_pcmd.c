/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_all_pcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:57 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 14:27:39 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "px.h"
#include "libft.h"

int	px_fork_all_pcmd(t_px_pipe_cmd **pipe_cmd)
{
	pid_t	last_pid;
	int		proc_cnt;
	int		in_pipe[2];

	proc_cnt = 0;
	if (pipe(in_pipe) == -1)
		return (-1);
	while (pipe_cmd[proc_cnt] != NULL)
	{
		last_pid = px_fork_for_pipe(pipe_cmd[proc_cnt], in_pipe);
		if (last_pid == 0)
		{
			if (px_execve(pipe_cmd[proc_cnt]) == -1)
				return (-1);
		}
		else if (last_pid == -1)
			return (px_close_pipe(in_pipe), -1);
		proc_cnt++;
	}
	return (px_int_wait_termed(proc_cnt, last_pid));
}
