/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:08:24 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/01 19:08:24 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "px.h"

int	px_fork_write(char *file, int pre_pipe[2], int now_pipe[2])
{
	int	cpid;
	int	fd;

	cpid = fork();
	if (cpid == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT, S_IRWXU);
		if (fd == -1)
			exit(1);
		close(pre_pipe[1]);
		close(now_pipe[0]);
		close(now_pipe[1]);
		if (px_read_and_write(pre_pipe[0], fd) == -1)
			exit(1);
		close(pre_pipe[0]);
		close(fd);
		exit(0);
	}
	return (cpid);
}
