/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:20:45 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 14:27:09 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "px.h"

int	px_execve(t_px_pipe_cmd *pipe_cmd)
{
	extern char	**environ;

	// PATH がない場合、No such file or ...
	// abs_path == NULL -> command_not found

	execve(pipe_cmd->abs_path, pipe_cmd->arguments, environ);
	px_set_errinfo(pipe_cmd->arguments[0]);
	return (-1);
}
