/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_is_permission_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:04:19 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 16:04:30 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <errno.h>

bool	px_is_permission_error(int eno)
{
	if (eno == EACCES
		|| eno == EISDIR
		|| eno == EPERM)
		return (true);
	else
		return (false);
}
