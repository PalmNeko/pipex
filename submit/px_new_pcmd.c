/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_new_pcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:40:33 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 12:46:22 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

/**
 * here_fd < 0 unset
 * here_fd >= 0 setted
 */
t_px_pipe_cmd	*px_new_pcmd(
						char *infile,
						char *outfile,
						char *command,
						int here_fd)
{
	t_px_pipe_cmd	*pipe_cmd;

	if (command == NULL)
		return (NULL);
	pipe_cmd = (t_px_pipe_cmd *)malloc(sizeof(t_px_pipe_cmd));
	if (pipe_cmd == NULL)
		return (NULL);
	ft_memset(pipe_cmd, 0, sizeof(t_px_pipe_cmd));
	pipe_cmd->here_fd = here_fd;
	pipe_cmd->infile = infile;
	pipe_cmd->outfile = outfile;
	pipe_cmd->command = command;
	pipe_cmd->arguments = ft_split(pipe_cmd->command, ' ');
	if (pipe_cmd->arguments == NULL)
		return (px_destroy_pcmd(pipe_cmd), NULL);
	pipe_cmd->abs_path = px_resolve_command_path(pipe_cmd->arguments[0]);
	if (pipe_cmd->abs_path == NULL && errno == ENOMEM)
		return (px_destroy_pcmd(pipe_cmd), NULL);
	return (pipe_cmd);
}
