/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_termed_null.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:52:11 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 12:44:47 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	free_termed_null(char **mems)
{
	char	**iter;

	if (mems == NULL)
		return ;
	iter = mems;
	while (*iter != NULL)
	{
		free(*iter);
		iter++;
	}
	free(mems);
}
