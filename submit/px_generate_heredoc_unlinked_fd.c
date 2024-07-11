/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_generate_heredoc_unlinked_fd.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:18:27 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 19:22:18 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "get_next_line.h"

int	px_write_until_deliminator(int in_fd, int out_fd, char *deliminator);
int	px_here_doc_stdin(int out_fd, char *deliminator);

int	px_generate_heredoc_unlinked_fd(char *deliminator)
{
	int		fd;
	int		rdonly_fd;
	char	template[11];

	ft_strlcpy(template, "tmp.XXXXXX", 11);
	fd = ft_mkostemp(template, 0);
	if (fd == -1)
		return (-1);
	rdonly_fd = open(template, O_RDONLY);
	if (rdonly_fd == -1)
		return (close(fd), -1);
	if (unlink(template) == -1)
		return (close(fd), close(rdonly_fd), -1);
	if (px_here_doc_stdin(fd, deliminator) == -1)
		return (close(fd), close(rdonly_fd), -1);
	close(fd);
	return (rdonly_fd);
}

int	px_here_doc_stdin(int out_fd, char *deliminator)
{
	int	read_term;

	read_term = px_write_until_deliminator(0, out_fd, deliminator);
	if (read_term == -1)
		return (-1);
	return (0);
}

int	px_write_until_deliminator(int in_fd, int out_fd, char *deliminator)
{
	char	*check_deliminator;
	char	*line;
	int		read_term;

	read_term = 0;
	check_deliminator = ft_strjoin(deliminator, "\n");
	if (check_deliminator == NULL)
		return (-1);
	errno = 0;
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(in_fd);
	while (line != NULL)
	{
		read_term = ft_strcmp(line, check_deliminator) == 0;
		if (read_term)
			break ;
		ft_putstr_fd(line, out_fd);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(in_fd);
	}
	free(line);
	free(check_deliminator);
	return ((int)ft_ifl(errno != 0, -1, read_term));
}
