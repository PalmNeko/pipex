/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_all_pcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:57 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 16:51:20 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "px.h"
#include "libft.h"

int	px_run_child_process(t_px_pipe_cmd *pipe_cmd);

/**
 * @return exit status
 */
int	px_run_all_pcmd(t_px_pipe_cmd **pipe_cmd)
{
	pid_t	last_pid;
	int		index;
	int		proc_cnt;
	int		in_pipe[2];

	proc_cnt = 0;
	while (pipe_cmd[proc_cnt] != NULL)
		proc_cnt++;
	if (pipe(in_pipe) == -1)
		return (1);
	index = 0;
	while (index < proc_cnt)
	{
		last_pid = px_fork_for_pipe(pipe_cmd[index], in_pipe);
		if (last_pid <= 0)
			break ;
		index++;
	}
	if (last_pid == 0)
		return (px_run_child_process(pipe_cmd[index]));
	else if (last_pid == -2)
		return (1);
	px_close_pipe(in_pipe);
	return (px_int_wait_termed(index, last_pid));
}

int	px_run_child_process(t_px_pipe_cmd *pipe_cmd)
{
	int	status;

	status = px_execve(pipe_cmd);
	px_set_errinfo(pipe_cmd->arguments[0]);
	return (status);
}
