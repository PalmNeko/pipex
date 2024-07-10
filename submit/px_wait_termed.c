/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_wait_termed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:15:42 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 16:42:41 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int		px_stat_to_exit_stat(int stat);
pid_t	px_waitpid_termed(pid_t pid, int *stat, int options);
pid_t	px_wait_termed(int *stat);

/**
 * @brief wait it which child process is terminated.
 * @param times number of children waiting.
 * @return 0 if succeed. -1 if failed and set errno.
 */
int	px_int_wait_termed(int child_cnt, pid_t last_pid)
{
	int		index;
	int		exit_stat;
	int		tmp_stat;
	pid_t	pid;

	exit_stat = 0;
	index = 0;
	px_waitpid_termed(last_pid, &tmp_stat, 0);
	index++;
	if (px_stat_to_exit_stat(tmp_stat) != 0)
		exit_stat = px_stat_to_exit_stat(tmp_stat);
	while (index < child_cnt)
	{
		pid = px_wait_termed(&tmp_stat);
		if (pid == -1)
			return (-1);
		index++;
	}
	return (exit_stat);
}

int	px_stat_to_exit_stat(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (128 + WTERMSIG(stat));
	else
		return (0);
}

pid_t	px_waitpid_termed(pid_t pid, int *stat, int options)
{
	pid_t	ret;

	while (1)
	{
		ret = waitpid(pid, stat, options);
		if (ret == -1)
			return (ret);
		if (WIFEXITED(*stat) || WIFSIGNALED(*stat))
			break ;
	}
	return (ret);
}

pid_t	px_wait_termed(int *stat)
{
	return (px_waitpid_termed(-1, stat, 0));
}
