/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_new_pcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:40:33 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 15:12:11 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "libft.h"
#include <stdlib.h>

t_px_pipe_cmd	*px_new_pcmd(
							char *infile, char *outfile, char *command)
{
	t_px_pipe_cmd	*pipe_cmd;

	pipe_cmd = (t_px_pipe_cmd *)malloc(sizeof(t_px_pipe_cmd));
	if (pipe_cmd == NULL)
		return (NULL);
	pipe_cmd->infile = NULL;
	pipe_cmd->outfile = NULL;
	pipe_cmd->command = NULL;
	pipe_cmd->infile = ft_strdup(infile);
	if (pipe_cmd->infile == NULL)
		return (px_destroy_pipeline_command(pipe_cmd), NULL);
	pipe_cmd->outfile = ft_strdup(outfile);
	if (pipe_cmd->outfile == NULL)
		return (px_destroy_pipeline_command(pipe_cmd), NULL);
	pipe_cmd->command = ft_strdup(command);
	if (pipe_cmd->command == NULL)
		return (px_destroy_pipeline_command(pipe_cmd), NULL);
	return (pipe_cmd);
}
