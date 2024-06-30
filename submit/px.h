/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:57:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/06/30 13:16:59 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_H
# define PX_H

char	*px_store_memory_from_input(int fd, const char *deliminator);
int		px_main(int argc, char *argv[]);
int		px_pipex_from_file(int argc, char *argv[]);
int		px_pipex_here_doc(int argc, char *argv[]);
void	px_print_error(int px_main_error);

#endif
