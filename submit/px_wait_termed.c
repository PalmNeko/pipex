/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_wait_termed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:15:42 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/03 15:26:45 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief wait it which child process is terminated.
 * @param times number of children waiting.
 * @return 0 if succeed. -1 if failed and set errno.
 */
int	px_wait_termed(int child_cnt, pid_t last_pid)
{
	int		index;
	int		stat;
	int		last_stat;
	pid_t	pid;

	last_stat = 0;
	index = 0;
	while (index < child_cnt)
	{
		pid = wait(&stat);
		if (pid == -1)
			return (-1);
		else if (pid == last_pid)
			last_stat = stat;
		if (WIFEXITED(stat) || WIFSIGNALED(stat))
			index++;
	}
	if (WIFEXITED(last_stat))
		return (WEXITSTATUS(last_stat));
	else if (WIFSIGNALED(last_stat))
		return (128 + WTERMSIG(last_stat));
	else
		return (0);
}
