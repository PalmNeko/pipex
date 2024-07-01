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

#include <unistd.h>
#include <stdlib.h>

extern char **environ;

int	px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2])
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		dup2(pre_pipe[0], 0);
		dup2(now_pipe[1], 1);
		close(pre_pipe[0]);
		close(pre_pipe[1]);
		close(now_pipe[0]);
		close(now_pipe[1]);
		if (execve(cmd, (char *[]){cmd, NULL}, environ) == -1)
		{
			write(1, "error\n", 6);
			exit(1);
		}
	}
	return (cpid);
}
