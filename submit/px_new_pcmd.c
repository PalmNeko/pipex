/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_new_pcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:40:33 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 15:47:06 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

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

	pipe_cmd = (t_px_pipe_cmd *)malloc(sizeof(t_px_pipe_cmd));
	if (pipe_cmd == NULL)
		return (NULL);
	pipe_cmd->here_fd = here_fd;
	pipe_cmd->infile = infile;
	pipe_cmd->outfile = outfile;
	pipe_cmd->command = command;
	return (pipe_cmd);
}
