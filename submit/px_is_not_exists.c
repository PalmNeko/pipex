/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_is_not_exists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:04:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 16:16:24 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <errno.h>

bool	px_is_not_exists(int eno)
{
	if (eno == EFAULT)
		return (true);
	else
		return (false);
}
