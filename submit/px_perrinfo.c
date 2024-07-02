/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_perrinfo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:42:46 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 19:48:08 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void	px_perrinfo(char *info)
{
	char	*errstr;

	errstr = strerror(errno);
	ft_putstr_fd(errstr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(info, 2);
	errno = 0;
	return ;
}