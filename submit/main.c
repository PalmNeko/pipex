/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:57:36 by tookuyam          #+#    #+#             */
/*   Updated: 2024/06/30 13:11:01 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"

int	main(int argc, char *argv[])
{
	int	result;

	result = px_main(argc, argv);
	if (result != 0)
	{
		px_print_error(result);
		return (1);
	}
	return (0);
}
