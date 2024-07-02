/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_close_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:13:04 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 13:49:54 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	px_close_pipe(int pipe[2])
{
	if (close(pipe[0]) == -1)
		return (-1);
	else if (close(pipe[1]) == -1)
		return (-1);
	else
		return (0);
}
