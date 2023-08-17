/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:58:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 14:08:42 by sotanaka         ###   ########.fr       */
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

//-------typedef-------
typedef struct s_dexec
{
	char	**matrix_envpath;
	char	*cmd_path;
	char	**cmd_opts;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	int		flag_pipe;
	int		flag_builtin;
}	t_dexec;

typedef struct s_intr
{
	int		*pipe;
	int		flag_wait;
}	t_intr;

typedef struct s_intr
{
	int		*pipe;
	int		flag_wait;
}	t_intr;

//-------prototype-------
//redirect
int		scan_btree_io(t_dexec *dexec, t_ast *node);
//cmd
int		scan_path_prog(t_dexec *dexec, t_ast *node);
//cmd util1
int		directory_is(char *path);
int		path_is_envp(char *cmd, t_dexec *dexec);
//cmd util2
int		ft_access_wrap(char *path, int flag);
int		ft_stat_wrap(char *path, int flag);
int		check_cmdpath(char *cmd_path, int flag);
int		check_cmdpath_hub(t_dexec *dexec, char *prog);
//utils
char	*get_cmd_path(t_ast *node);
char	*get_cmd_prog(t_ast *node);
char	**get_argv(t_ast *node);
//do
int		fd_close(int fd_in, int fd_out);
int		exec_do(t_dexec *dexec, t_ast *node, int flag);

#endif