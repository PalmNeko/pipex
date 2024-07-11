/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_for_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:32:37 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 14:09:07 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "px.h"
#include "libft.h"

int	px_set_infd(t_px_pipe_cmd *pipe_cmd, int in_pipe[2]);
int	px_set_outfd(t_px_pipe_cmd *pipe_cmd, int out_pipe[2]);

/**
 * @param in_param input pipe. this must be not NULL.
 * @return 0 if child process. -1 if some error (child or parent). > 0 if parent
 * @note overwrite in_pipe
 */
pid_t	px_fork_for_pipe(t_px_pipe_cmd *pipe_cmd, int in_pipe[2])
{
	int		out_pipe[2];
	pid_t	cpid;

	if (pipe(out_pipe) == -1)
		return (-1);
	cpid = fork();
	if (cpid == 0)
	{
		if (px_set_infd(pipe_cmd, in_pipe) != 0)
			return (px_close_pipe(in_pipe), px_close_pipe(out_pipe), px_set_errinfo(pipe_cmd->infile), -1);
		px_close_pipe(in_pipe);
		if (px_set_outfd(pipe_cmd, out_pipe) != 0)
			return (px_close_pipe(out_pipe), px_set_errinfo(pipe_cmd->outfile), -1);
		px_close_pipe(out_pipe);
		return (0);
	}
	px_close_pipe(in_pipe);
	ft_memmove(in_pipe, out_pipe, sizeof(int) * 2);
	return (cpid);
}

int	px_set_infd(t_px_pipe_cmd *pipe_cmd, int in_pipe[2])
{
	int	fd;

	if (pipe_cmd->infile != NULL)
		fd = open(pipe_cmd->infile, O_RDONLY);
	else if (pipe_cmd->here_fd != -1)
		fd = pipe_cmd->here_fd;
	else
		fd = in_pipe[0];
	if (fd == -1)
		return (-1);
	dup2(fd, 0);
	if (fd != in_pipe[0])
		close(fd);
	return (0);
}

int	px_set_outfd(t_px_pipe_cmd *pipe_cmd, int out_pipe[2])
{
	int		fd;
	int		flag;
	mode_t	mode;

	flag = O_WRONLY | O_CREAT;
	if (pipe_cmd->here_fd != -1)
		flag |= O_TRUNC;
	else
		flag |= O_APPEND;
	mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
	if (pipe_cmd->outfile != NULL)
		fd = open(pipe_cmd->outfile, flag, mode);
	else if (pipe_cmd->here_fd != -1)
		fd = pipe_cmd->here_fd;
	else
		fd = out_pipe[1];
	if (fd == -1)
		return (-1);
	dup2(fd, 1);
	if (fd != out_pipe[1])
		close(fd);
	return (0);
}