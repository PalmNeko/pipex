/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipex_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:14:53 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/01 18:08:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "px_errors.h"
#include "libft.h"

extern char **environ;

int	px_read_and_write(int read_fd, int write_fd);
int	px_fork_write(char *file, int pre_pipe[2], int now_pipe[2]);
int	px_fork_read(char *file, int pre_pipe[2], int now_pipe[2]);
int	px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2]);

int	px_pipex_from_file(int argc, char *argv[])
{
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
	int stat;
	index = 1;
	while (index < argc)
	{
		wait(&stat);
		while (! WIFEXITED(stat))
    		wait(&stat);
		index++;
	}
    close(pre_fds[1]);
    close(pre_fds[0]);
    return (0);
}

int	px_read_and_write(int read_fd, int write_fd)
{
	ssize_t	len;
	char	buf[1024];

	len = read(read_fd, buf, sizeof(buf));
	while (len > 0)
	{
		if (write(write_fd, buf, len) == -1)
			return (-1);
		len = read(read_fd, buf, sizeof(buf));
	}
	if (len == -1)
		return (-1);
	return (0);
}

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
