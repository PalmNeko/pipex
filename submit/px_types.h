/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:54:24 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/12 18:33:22 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_TYPES_H
# define PX_TYPES_H

# include <stdbool.h>

typedef struct s_px_pipeline_command
{
	char	*infile;
	char	*outfile;
	char	*command;
	char	*abs_path;
	char	**arguments;
	int		here_fd;
	bool	is_here_doc;
}	t_px_pipe_cmd;

#endif
