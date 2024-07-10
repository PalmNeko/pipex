/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_all_pcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:57 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 16:59:40 by tookuyam         ###   ########.fr       */
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
	int		out_pipe[2];

	proc_cnt = 0;
	if (pipe(in_pipe) == -1)
		return (-1);
	while (pipe_cmd[proc_cnt] != NULL)
	{
		if (pipe(out_pipe) == -1)
			return (-1);
		last_pid = px_fork_for_pcmd(pipe_cmd[proc_cnt], in_pipe, out_pipe);
		px_close_pipe(in_pipe);
		ft_memmove(in_pipe, out_pipe, sizeof(int) * 2);
		if (last_pid == -1)
			return (px_close_pipe(out_pipe), -1);
		proc_cnt++;
	}
	return (px_int_wait_termed(proc_cnt, last_pid));
}
