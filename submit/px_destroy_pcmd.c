/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_destroy_pipeline_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:45:39 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 15:11:15 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_types.h"
#include "libft.h"
#include <stdlib.h>

t_px_pipe_cmd	*px_destroy_pcmd(t_px_pipe_cmd *pipe_cmd)
{
	free(pipe_cmd->infile);
	free(pipe_cmd->outfile);
	free(pipe_cmd->command);
}
