/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:57:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 19:31:02 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_H
# define PX_H

# include <sys/types.h>
# include "px_types.h"

char			*px_store_memory_from_input(int fd, const char *deliminator);
int				px_main(int argc, char *argv[]);
int				px_pipex_from_file(int argc, char *argv[]);
int				px_pipex_here_doc(int argc, char *argv[]);
void			px_print_error(int px_main_error);
int				px_fork_here_doc(
					char *deliminator, int pre_pipe[2], int now_pipe[2]);
int				px_fork_write(char *file, int pre_pipe[2], int now_pipe[2]);
int				px_fork_write_append(
					char *file, int pre_pipe[2], int now_pipe[2]);
int				px_fork_read(char *file, int pre_pipe[2], int now_pipe[2]);
int				px_fork_execve(char *cmd, int pre_pipe[2], int now_pipe[2]);
int				px_read_and_write(int read_fd, int write_fd);
int				px_close_pipe(int pipe[2]);
void			px_errexit_child(void);
void			px_perrinfo(int status);
void			px_perror_cmd_not_found(char *info);
void			px_pe(char *info);
void			px_destroy_pcmd(t_px_pipe_cmd *pipe_cmd);
t_px_pipe_cmd	*px_new_pcmd(
					char *infile,
					char *outfile,
					char *command,
					int here_fd);
t_px_pipe_cmd	**px_gen_pcmd_for_heredoc(int argc, char *argv[]);
t_px_pipe_cmd	**px_gen_pcmd_for_file(int argc, char *argv[]);
void			px_free_pcmd_array(t_px_pipe_cmd **pipe_cmds);
int				px_generate_heredoc_unlinked_fd(char *deliminator);
void			px_free_errinfo(void);
char			*px_get_errinfo(void);
int				px_set_errinfo(char *errinfo);
int				px_execve(t_px_pipe_cmd *pipe_cmd);
pid_t			px_fork_for_pcmd(
					t_px_pipe_cmd *pipe_cmd, int in_pipe[2], int out_pipe[2]);
int				px_int_wait_termed(int child_cnt, pid_t last_pid);
int				px_run_all_pcmd(t_px_pipe_cmd **pipe_cmd);
char			*px_resolve_command_path(char *command);
void			free_termed_null(char **mems);
pid_t			px_fork_for_pipe(t_px_pipe_cmd *pipe_cmd, int in_pipe[2]);
int				px_get_error(void);
void			px_set_error(int errno);
bool			px_is_permission_error(int eno);
bool			px_is_not_exists(int eno);

#endif
