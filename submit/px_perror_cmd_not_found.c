/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_perror_cmd_not_found.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:42:46 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/10 13:27:39 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void	px_perror_cmd_not_found(char *info)
{

	ft_putstr_fd("command not found", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(info, 2);
	errno = 0;
	return ;
}
