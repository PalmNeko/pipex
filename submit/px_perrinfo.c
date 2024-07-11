/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_perrinfo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:42:46 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 16:58:59 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "px.h"
#include "px_errors.h"

char	*px_get_error_str(int status);

void	px_perrinfo(int status)
{
	char	*errstr;

	errstr = px_get_error_str(status);
	if (errstr == NULL)
		return ;
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

char	*px_get_error_str(int status)
{
	if (errno == 0)
		return (NULL);
	else if (status == 127 && errno == ENOENT)
		return (strerror(errno));
	else if (status == 127 && px_is_not_exists(errno))
		return ("command not found");
	else if (errno == PX_EARGCNT)
		return ("You must include 2 command.");
	else if (errno < 0)
		return ("Unspecified Error");
	else
		return (strerror(errno));
}
