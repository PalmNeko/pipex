/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:11:20 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 15:24:37 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "px.h"

pid_t	px_fork_here_doc(char *deliminator, int pre_pipe[2], int now_pipe[2])
{
	pid_t	cpid;
	int		fd;

	fd = px_generate_heredoc_unlinked_fd(deliminator);
	if (fd == -1)
		return (px_perrinfo("here_doc"), -1);
	cpid = fork();
	if (cpid == 0)
	{
		close(pre_pipe[0]);
		close(pre_pipe[1]);
		close(now_pipe[0]);
		if (px_read_and_write(fd, now_pipe[1]) == -1)
			exit(1);
		close(now_pipe[1]);
		close(fd);
		exit(0);
	}
	close(fd);
	return (cpid);
}
