/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:20:45 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 18:25:29 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "px.h"
#include "libft.h"
#include <errno.h>

/**
 * @return 125 generic error. 127 command not found. 126 permission error.
 */
#include <stdio.h>
int	px_execve(t_px_pipe_cmd *pipe_cmd)
{
	extern char	**environ;
	char		*path;

	path = ft_getenv("PATH");
	if (path == NULL || path[0] == '\0')
		return (ft_set_errno(ENOENT), 127);
	execve(pipe_cmd->abs_path, pipe_cmd->arguments, environ);
	if (px_is_permission_error(errno))
		return (126);
	else if (px_is_not_exists(errno))
		return (127);
	else
		return (127);
}
