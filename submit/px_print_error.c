/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:13:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 19:56:19 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "px_errors.h"
#include "libft.h"

char	*px_str_error(int px_main_error);

void	px_print_error(int px_main_error)
{
	char	*err_str;

	if (errno != 0 && px_main_error == -1)
		perror(NULL);
	else if (px_main_error > 0)
	{
		err_str = px_str_error(px_main_error);
		if (err_str != NULL)
		{
			ft_putstr_fd(px_str_error(px_main_error), 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return ;
}

char	*px_str_error(int px_main_error)
{
	if (px_main_error == PX_EARGCNT)
		return ("You must include 2 command.");
	else
		return ("Unspecified Error");
	return (NULL);
}
