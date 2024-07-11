/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_destroy_pcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:45:39 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 12:44:03 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_types.h"
#include "libft.h"
#include "px.h"
#include <stdlib.h>

void	px_destroy_pcmd(t_px_pipe_cmd *pipe_cmd)
{
	free_termed_null(pipe_cmd->arguments);
	free(pipe_cmd->abs_path);
	free(pipe_cmd);
}
