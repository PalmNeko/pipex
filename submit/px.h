/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:57:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/12 18:34:37 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_H
# define PX_H

# include <sys/types.h>
# include "px_types.h"

bool			px_is_not_exists(int eno);
bool			px_is_permission_error(int eno);
char			*px_get_errinfo(void);
char			*px_resolve_command_path(char *command);
int				px_close_pipe(int pipe[2]);
int				px_execve(t_px_pipe_cmd *pipe_cmd);
int				px_generate_heredoc_unlinked_fd(char *deliminator);
int				px_get_error(void);
int				px_int_wait_termed(int child_cnt, pid_t last_pid);
int				px_main(int argc, char *argv[]);
int				px_run_all_pcmd(t_px_pipe_cmd **pipe_cmd);
int				px_set_errinfo(char *errinfo);
pid_t			px_fork_for_pipe(t_px_pipe_cmd *pipe_cmd, int in_pipe[2]);
t_px_pipe_cmd	**px_gen_pcmd_for_file(int argc, char *argv[]);
t_px_pipe_cmd	**px_gen_pcmd_for_heredoc(int argc, char *argv[]);
t_px_pipe_cmd	*px_new_pcmd(
					char *infile, char *outfile, char *command, int here_fd);
void			free_termed_null(char **mems);
void			px_destroy_pcmd(t_px_pipe_cmd *pipe_cmd);
void			px_free_errinfo(void);
void			px_free_pcmd_array(t_px_pipe_cmd **pipe_cmds);
void			px_perrinfo(int status);
void			px_perror_cmd_not_found(char *info);
void			px_print_error(int px_main_error);
void			px_set_error(int errno);

#endif
