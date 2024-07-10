/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:20:45 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 16:30:07 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	px_execve(char *abs_path, char **arguments)
{
	extern char	**environ;

	// PATH がない場合、No such file or ...
	// abs_path == NULL -> command_not found

	execve(abs_path, arguments, environ);
	px_set_errinfo(arguments[0]);
	return (-1);
}
