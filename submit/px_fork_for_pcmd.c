/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_for_pcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:39:39 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 16:31:37 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "px.h"

int	px_set_fds(t_px_pipe_cmd *pipe_cmd, int in_pipe[2], int out_pipe[2]);
int	px_set_infd(t_px_pipe_cmd *pipe_cmd, int in_pipe[2]);
int	px_set_outfd(t_px_pipe_cmd *pipe_cmd, int out_pipe[2]);

pid_t	px_for_for_pcmd(t_px_pipe_cmd *pipe_cmd, int in_pipe[2], int out_pipe[2])
{
	pid_t		cpid;
	char		*abs_path;
	char		**arguments;

	arguments = ft_split(pipe_cmd->command, ' ');
	if (arguments == NULL)
		return (-1);
	abs_path = px_resolve_command_path(arguments[0]);
	if (abs_path == NULL && errno != ENOENT)
		return (px_perrinfo(arguments[0]), free_termed_null(arguments), -1);
	cpid = fork();
	if (cpid == 0)
	{
		if (px_set_fds(pipe_cmd, in_pipe, out_pipe) != 0
			|| px_execve(abs_path, arguments) == -1)
			return (free_termed_null(arguments), free(abs_path), -2);
	}
	return (free_termed_null(arguments), free(abs_path), cpid);
}

int	px_set_fds(t_px_pipe_cmd *pipe_cmd, int in_pipe[2], int out_pipe[2])
{
	if (px_set_infd(pipe_cmd, in_pipe) != 0)
		return (-1);
	else if (px_set_outfd(pipe_cmd, out_pipe) != 0)
		return (-1);
	return (0);
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
		return (px_set_errinfo(pipe_cmd->infile), -1);
	dup2(fd, 0);
	px_close_pipe(in_pipe);
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
		return (px_set_errinfo(pipe_cmd->outfile), -1);
	dup2(fd, 1);
	px_close_pipe(out_pipe);
	if (fd != out_pipe[1])
		close(fd);
	return (0);
}
