/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_read_and_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:18:44 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/01 19:18:44 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	px_read_and_write(int read_fd, int write_fd)
{
	ssize_t	len;
	char	buf[1024];

	len = read(read_fd, buf, sizeof(buf));
	while (len > 0)
	{
		if (write(write_fd, buf, len) == -1)
			return (-1);
		len = read(read_fd, buf, sizeof(buf));
	}
	if (len == -1)
		return (-1);
	return (0);
}
