/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_gen_pcmd_for_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:40:10 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 15:26:22 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

t_px_pipe_cmd	**px_gen_pcmd_for_heredoc(int argc, char *argv[])
{
	t_px_pipe_cmd	**pipe_cmds;
	const int		others_argc = 4;
	int				index;
	int				size;

	if (argc < 6)
		return (ft_set_errno(ERANGE), NULL);
	size = (argc - others_argc + 1);
	pipe_cmds = (t_px_pipe_cmd **)malloc(sizeof(t_px_pipe_cmd *) * size);
	if (pipe_cmds == NULL)
		return (NULL);
	ft_memset(pipe_cmds, 0, sizeof(t_px_pipe_cmd *) * size);
	index = 3;
	while (index < argc - 1)
	{
		pipe_cmds[index - 3] = _px_gen_pipe_cmd_for_heredoc(index, argc, argv);
		if (pipe_cmds[index - 3] == NULL)
			return (px_free_pipe_cmd_array(pipe_cmds) , NULL);
		index++;
	}
	return (pipe_cmds);
}

t_px_pipe_cmd	*_px_gen_pipe_cmd_for_heredoc(int index, int argc, char *argv[])
{
	int	here_fd;

	if (index == 3)
	{
		here_fd = px_generate_heredoc_unlinked_fd(argv[index - 1]);
		if (here_fd == -1)
			return (NULL);
		return px_new_pcmd(NULL, NULL, argv[index], here_fd);
	}
	else if (index < argc - 2)
		return px_new_pcmd(NULL, NULL, argv[index], -1);
	else
		return px_new_pcmd(NULL, argv[index - 1], argv[index], -1);
}
