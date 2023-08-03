/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:34:04 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/03 17:14:13 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//-------define-------
//exit status
# define ACCESS_FOK 1
# define ACCESS_XOK 2
# define STAT_ISDIR 3
# define CMD_SIMPLE 2
# define EX_CTLR_C 1
# define EX_FILE_OPEN_ERR 1
# define IS_A_DIRECTORY 1
# define CMD_PERM_DENIED 126
# define CMD_NOTFOUND 127
# define EX_CTRL_BACKSLASH 131
# define EX_SYNTAX_ERROR 258

//-------include-------
# include <minishell.h>

//-------typedef-------
typedef struct s_dexec
{
	char	**matrix_envpath;
	char	*cmd_path;
	char	**cmd_opts;
	int		fd_in;
	int		fd_out;
}	t_dexec;

typedef struct s_tree
{
	int				type;
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//-------prototype-------
//ft_exec_env_path
char	**ft_split_by_token(char **matrix, char token);
//ft_exec_cmd_path
char	*ft_get_cmdpath(char *path, char *prog, t_dexec *dexec);
//ft_exec_scan_btree
int		scan_btree_fd(t_dexec *dexec, t_ast *node);
int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node);
//ft_print_error
int		ft_mes_error(char *message);
int		ft_print_perror(char *original_message);
int 	cmd_cant_use(char *cmd, int flag);
//ft_exec_open_file
int		ft_open_file(char *file_redirect, int flag_redirect, int fd_io);
//ft_exec_do
int		ft_exec_forked(t_dexec *dexec, t_ast *node);

#endif