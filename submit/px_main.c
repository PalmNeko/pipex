/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:11:34 by tookuyam          #+#    #+#             */
/*   Updated: 2024/06/30 14:42:35 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "px_errors.h"
#include "libft.h"

int	px_main(int argc, char *argv[])
{
	int result;

	if (argc < 5)
		return (PX_EARGCNT);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		result = px_pipex_here_doc(argc, argv);
	else
		result = px_pipex_from_file(argc, argv);
	return (result);
}
