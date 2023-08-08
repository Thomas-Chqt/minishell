/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:58:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/08 14:10:07 by hotph            ###   ########.fr       */
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
# define EX_CTRL_BACKSLASH 131
# define EX_SYNTAX_ERROR 258

//-------include-------
# include "parser.h"

//-------typedef-------
typedef struct s_dexec
{
	char	**matrix_envpath;
	char	*cmd_path;
	char	**cmd_opts;
	int		fd_in;
	int		fd_out;
}	t_dexec;

//-------prototype-------
//scan_btree_pipe
int		scan_btree_pipe(int fd_in, int fd_out, t_ast *node);
//ft_exec_env_path
char	**ft_split_by_token(char **matrix, char token);
//ft_exec_cmd_path
char	*ft_get_cmdpath(char *path, char *prog, t_dexec *dexec);
//getpath_util
int		ft_access_wrap(char *path, int flag);
int		ft_stat_wrap(char *path, int flag);
int		check_cmdpath(char *cmd_path, int flag);
//ft_exec_scan_btree
int		scan_btree_fd(t_dexec *dexec, t_ast *node);
int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node);
//ft_print_error
int		ft_mes_error(char *message);
int		ft_print_perror(char *original_message);
int 	minishell_error(char *cmd, int flag, char *message);
//ft_exec_open_file
int		ft_open_file(char *file_redirect, int flag_redirect, int fd_io);
//ft_exec_do
int		ft_exec_forked(t_dexec *dexec, t_ast *node);
char	*get_cmd_path(t_ast *node);
char	*get_cmd_prog(t_ast *node);
int		get_argc(t_ast *node);
char	**get_argv(t_ast *node);

#endif