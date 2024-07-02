/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:57:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/02 18:02:08 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_H
# define PX_H

char	*px_store_memory_from_input(int fd, const char *deliminator);
int		px_main(int argc, char *argv[]);
int		px_pipex_from_file(int argc, char *argv[]);
int		px_pipex_here_doc(int argc, char *argv[]);
void	px_print_error(int px_main_error);
int		px_fork_here_doc(char *deliminator, int pre_pipe[2], int now_pipe[2]);
int		px_fork_write(char *file, int pre_pipe[2], int now_pipe[2]);
int		px_fork_read(char *file, int pre_pipe[2], int now_pipe[2]);
int		px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2]);
int		px_read_and_write(int read_fd, int write_fd);
int		px_close_pipe(int pipe[2]);
int		px_wait_termed(int child_cnt);

#endif
