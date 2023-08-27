/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:58:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 17:17:59 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//-------define-------
//exit status
# define ACCESS_FOK 1
# define ACCESS_ROK 2
# define ACCESS_WOK 3
# define ACCESS_XOK 4
# define STAT_ISDIR 3
# define STAT_ISREG 4
# define CMD_SIMPLE 2
# define EX_CTLR_C 1
# define EX_FILE_OPEN_ERR 1
# define IS_A_DIRECTORY 1
# define CMD_CANT_EXEC 126
# define CMD_NOTFOUND 127

//-------include-------
# include "parser.h"
# include "signals.h"
# include "expander.h"

//-------typedef-------
typedef struct s_exe
{
	char	**matrix_envpath;
	char	*cmd_path;
	char	**cmd_opts;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	int		flag_pipe;
	int		flag_pipe_close;
	int		flag_builtin;
}	t_exe;

typedef struct s_intr
{
	int		*pipe;
	int		flag_pipe;
}	t_intr;

//-------prototype-------
//redirect
int		ft_open_file(char *file_redirect, int flag_redirect, int *fd_io);
int		scan_btree_io(t_exe *exe, t_ast *node);
//heredoc
char	*get_temporary_name10(char *namespace, char *name, int size_space);
int		ft_here_doc(char *delimiter, int *fd_in);
//prog
int		scan_path_prog(t_exe *exe, t_ast *node);
//prog util1
int		directory_is(char *path);
int		path_is_envp(char *cmd, t_exe *exe);
//prog util2
int		ft_access_wrap(char *path, int flag);
int		ft_stat_wrap(char *path, int flag);
int		check_cmdpath(char *cmd_path, int flag);
int		check_cmdpath_hub(t_exe *exe);
//exec_utils1
char	*get_cmd_path(t_ast *node, int *error);
char	*get_cmd_prog(t_ast *node, int *error);
char	**get_argv(t_ast *node);
int		get_argc(t_ast *node);
//exec_utils2
void	init_exe(int fd_in, int fd_out, t_exe *exe, t_intr *intr);
int		end_with_fd_close(t_exe *exe, int status);
int		skip_if_environment(t_ast **node);
void	minishell_unlink(void);
//do
int		exec_do(t_exe *exe, t_ast *node, int flag);
//do utils
int		fd_close(int fd_in, int fd_out);
int		set_redirect(t_exe *exe);

#endif