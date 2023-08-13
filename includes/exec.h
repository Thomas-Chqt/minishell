/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:58:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/13 11:47:43 by hotph            ###   ########.fr       */
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
//get_cmdpath
int		ft_get_cmdpath(char *path, char *prog, t_dexec *dexec);
//getpath_util
int		ft_access_wrap(char *path, int flag);
int		ft_stat_wrap(char *path, int flag);
int		check_cmdpath(char *cmd_path, int flag);
int		check_cmdpath_hub(t_dexec *dexec, char *prog);
char	**ft_split_by_token(char **matrix, char token);
//scan_btree
void	scan_btree_fd(t_dexec *dexec, t_ast *node);
int		scan_btree_pipe(int fd_in, int fd_out, t_ast *node, int flag);
//here_doc
int		ft_here_doc(char *delimiter, int fd_in);
//print_error
int		ft_mes_error(char *message);
int		ft_print_perror(char *original_message);
int		minishell_error(char *cmd, int flag, char *message);
//do
void	ft_exec_forked(t_dexec *dexec, t_ast *node);
//util
char	*get_cmd_path(t_ast *node);
char	*get_cmd_prog(t_ast *node);
int		get_argc(t_ast *node);
char	**get_argv(t_ast *node);

#endif