/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:57:36 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/03 15:51:25 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px.h"
#include "libft.h"

void	px_print_help(void);

int	main(int argc, char *argv[])
{
	int	result;

	if (argc < 5)
	{
		px_print_help();
		return (1);
	}
	result = px_main(argc, argv);
	if (result == -1)
	{
		px_print_error(result);
		return (1);
	}
	return (result);
}

void	px_print_help(void)
{
	ft_putstr_fd(
		"USAGE\n"
		" pipex file1 cmd1 cmd2... file2\n"
		" pipex here_doc DELIMINATOR cmd1 cmd2... file3\n"
		"\n"
		" file1 : input file\n"
		" file2 : output file which old file is truncated\n"
		" file3 : output file. write to end for appending\n"
		" cmd   : command\n", 1);
}
