/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:13:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/01 18:13:13 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "px.h"

int	px_fork_read(char *file, int pre_pipe[2], int now_pipe[2])
{
	int	cpid;
	int	fd;

	cpid = fork();
	if (cpid == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			exit(1);
		close(pre_pipe[0]);
		close(pre_pipe[1]);
		close(now_pipe[0]);
		if (px_read_and_write(fd, now_pipe[1]) == -1)
			exit(1);
		close(now_pipe[1]);
		close(fd);
		exit(0);
	}
	return (cpid);
}
