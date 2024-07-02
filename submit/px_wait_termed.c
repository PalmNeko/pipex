/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_wait_termed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:15:42 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 13:43:31 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief wait it which child process is terminated.
 * @param times number of children waiting.
 * @return 0 if succeed. -1 if failed and set errno.
 */
int	px_wait_termed(int child_cnt)
{
	int	index;
	int	stat;

	index = 1;
	while (index < child_cnt)
	{
		if (wait(&stat) == -1)
			return (-1);
		if (WIFEXITED(stat) || WIFSIGNALED(stat))
			index++;
	}
	return (0);
}
