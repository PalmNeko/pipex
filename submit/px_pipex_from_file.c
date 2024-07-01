/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipex_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:14:53 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/01 20:44:54 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "px_errors.h"
#include "px.h"

int	px_read_and_write(int read_fd, int write_fd);

int	px_pipex_from_file(int argc, char *argv[])
{
	int stat;
    int index;
    int pre_fds[2];
    int now_fds[2];

    pipe(pre_fds);
    index = 1;
    while (index < argc)
    {
		pipe(now_fds);
		if (index == 1)
		{
			if (px_fork_read(argv[index], pre_fds, now_fds) == -1)
				return (-1);
		}
		else if (index < argc - 1)
		{
			if (px_fork_execve(argv[index], pre_fds, now_fds) == -1)
				return (-1);
		}
		else if (index == argc - 1)
		{
			if (px_fork_write(argv[index], pre_fds, now_fds) == -1)
				return (-1);
		}
        close(pre_fds[0]);
        close(pre_fds[1]);
        pre_fds[0] = now_fds[0];
        pre_fds[1] = now_fds[1];
        index++;
    }
	index = 1;
	while (index < argc)
	{
		if (wait(&stat) == -1 && (perror("wait"), 1))
			break ;
		if (WIFEXITED(stat) || WIFSIGNALED(stat))
    		index++;
	}
    close(pre_fds[1]);
    close(pre_fds[0]);
    return (0);
}
