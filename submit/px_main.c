/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:11:34 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 16:09:47 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "px_errors.h"
#include "libft.h"
#include <stdio.h>

int	px_main(int argc, char *argv[])
{
	int				result;
	t_px_pipe_cmd	**cmds;

	if (argc < 5)
		return (ft_set_errno(PX_EARGCNT), 1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		cmds = px_gen_pcmd_for_heredoc(argc, argv);
	else
		cmds = px_gen_pcmd_for_file(argc, argv);
	if (cmds == NULL)
		return (1);
	result = px_run_all_pcmd(cmds);
	px_free_pcmd_array(cmds);
	return (result);
}
