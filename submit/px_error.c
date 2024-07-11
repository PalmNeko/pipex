/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:42:30 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 15:46:44 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	px_error(int errno, bool is_set)
{
	static int	eno;

	if (is_set)
	{
		eno = errno;
		return (0);
	}
	else
		return (eno);
}

void	px_set_error(int errno)
{
	px_error(errno, true);
}

int	px_get_error(void)
{
	return (px_error(0, true));
}
