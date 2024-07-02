/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:11:34 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 13:52:44 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "px_errors.h"
#include "libft.h"

int	px_main(int argc, char *argv[])
{
	int	result;

	if (argc < 5)
		return (PX_EARGCNT);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		result = px_pipex_here_doc(argc, argv);
	else
		result = px_pipex_from_file(argc, argv);
	return (result);
}
