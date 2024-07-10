/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free_pcmd_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:21:54 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 17:09:43 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "px.h"

void	px_free_pcmd_array(t_px_pipe_cmd **pipe_cmds)
{
	t_px_pipe_cmd	**top_ptr;

	top_ptr = pipe_cmds;
	while (*pipe_cmds != NULL)
	{
		px_destroy_pcmd(*pipe_cmds);
		pipe_cmds++;
	}
	free(top_ptr);
	return ;
}
