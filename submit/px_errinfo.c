/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_errinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:06:09 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 16:12:02 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "px.h"
#include <stdlib.h>

static char	*g_px_errinfo;

int	px_set_errinfo(char *errinfo)
{
	px_free_errinfo();
	if (errinfo != NULL)
	{
		g_px_errinfo = ft_strdup(errinfo);
		if (g_px_errinfo == NULL)
			return (-1);
	}
	return (0);
}

char	*px_get_errinfo(void)
{
	return (g_px_errinfo);
}

void	px_free_errinfo(void)
{
	free(g_px_errinfo);
	g_px_errinfo = NULL;
}
