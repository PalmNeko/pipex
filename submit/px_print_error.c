/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:13:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/06/30 14:23:44 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "px_errors.h"
#include "libft.h"

char	*px_str_error(int px_main_error);

void	px_print_error(int px_main_error)
{
	if (px_main_error == -1)
		perror(NULL);
	else
	{
		ft_putstr_fd(px_str_error(px_main_error), 2);
		ft_putstr_fd("\n", 2);
	}
	return ;
}

char	*px_str_error(int px_main_error)
{
	if (px_main_error == PX_EARGCNT)
		return ("You must pass four or more arguments.");
	return ("");
}
