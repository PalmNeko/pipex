/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:54:24 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 12:38:51 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_TYPES_H
# define PX_TYPES_H

#include <stdbool.h>

typedef int	(*t_f_px_fork)(char *argument, int pre_pipe[2], int now_pipe[2]);

typedef struct s_px_pipeline_command
{
	char	*infile;
	char	*outfile;
	char	*command;
	char	*abs_path;
	char	**arguments;
	int		here_fd;
}	t_px_pipe_cmd;

#endif
