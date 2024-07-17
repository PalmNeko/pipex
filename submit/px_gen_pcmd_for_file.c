/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_gen_pcmd_for_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:27:29 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/17 15:50:42 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

t_px_pipe_cmd	*_px_gen_pipe_cmd_for_file(int index, int argc, char *argv[]);

t_px_pipe_cmd	**px_gen_pcmd_for_file(int argc, char *argv[])
{
	t_px_pipe_cmd	**pipe_cmds;
	const int		others_argc = 3;
	int				index;
	int				size;

	if (argc < 5)
		return (ft_set_errno(ERANGE), NULL);
	size = (argc - others_argc + 1);
	pipe_cmds = (t_px_pipe_cmd **)malloc(sizeof(t_px_pipe_cmd *) * size);
	if (pipe_cmds == NULL)
		return (NULL);
	ft_memset(pipe_cmds, 0, sizeof(t_px_pipe_cmd *) * size);
	index = 2;
	while (index < argc - 1)
	{
		pipe_cmds[index - 2] = _px_gen_pipe_cmd_for_file(index, argc, argv);
		if (pipe_cmds[index - 2] == NULL)
			return (px_free_pcmd_array(pipe_cmds), NULL);
		index++;
	}
	return (pipe_cmds);
}

t_px_pipe_cmd	*_px_gen_pipe_cmd_for_file(int index, int argc, char *argv[])
{
	t_px_pipe_cmd	*pipe_cmd;

	if (index == 2)
		pipe_cmd = px_new_pcmd(argv[index - 1], NULL, argv[index], -1);
	else if (index < argc - 2)
		pipe_cmd = px_new_pcmd(NULL, NULL, argv[index], -1);
	else
		pipe_cmd = px_new_pcmd(NULL, argv[index + 1], argv[index], -1);
	return (pipe_cmd);
}
