/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:11:20 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/03 12:25:05 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "px.h"
#include "libft.h"
#include "get_next_line.h"

int px_generate_heredoc_unlinked_fd(char *deliminator);
int	px_write_until_deliminator(int out_fd, char	*deliminator);

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

int px_generate_heredoc_unlinked_fd(char *deliminator)
{
	int		fd;
	int		rdonly_fd;
	char	*template;

	template = ft_strdup("tmp.XXXXXX");
	if (template == NULL)
		return (-1);
	fd = ft_mkostemp(template, 0);
	if (fd == -1)
		return (free(template), -1);
	rdonly_fd = open(template, O_RDONLY);
	if (rdonly_fd == -1)
		return (free(template), close(fd), -1);
	if (unlink(template) == -1)
		return (free(template), close(fd), close(rdonly_fd), -1);
	free(template);
	if (px_write_until_deliminator(fd, deliminator) == -1)
		return (close(fd), close(rdonly_fd), -1);
	close(fd);
	return (rdonly_fd);
}

int	px_write_until_deliminator(int out_fd, char	*deliminator)
{
	char	*check_deliminator;
	char	*line;

	check_deliminator = ft_strjoin(deliminator, "\n");
	if (check_deliminator == NULL)
		return (-1);
	errno = 0;
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (line != NULL)
	{
		if (ft_strcmp(line, check_deliminator) == 0)
			break ;
		ft_putstr_fd(line, out_fd);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	free(line);
	free(check_deliminator);
	if (errno != 0)
		return (-1);
	else
		return (0);
}