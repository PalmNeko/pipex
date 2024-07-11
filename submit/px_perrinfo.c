/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_perrinfo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:42:46 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 14:20:31 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "px.h"

void	px_perrinfo(void)
{
	char	*errstr;

	errstr = strerror(errno);
	ft_putstr_fd(errstr, 2);
	if (px_get_errinfo() != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(px_get_errinfo(), 2);
	}
	ft_putstr_fd("\n", 2);
	errno = 0;
	return ;
}
