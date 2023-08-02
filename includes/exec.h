/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:34:04 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/01 19:03:25 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//-------define-------
//exit status
# define EX_CTLR_C 1
# define EX_FILE_OPEN_ERR 1
# define EX_IS_A_DIRECTORY 1
# define EX_CMD_PERM_DENIED 126
# define EX_CMD_NOT_FOUND 127
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
}	t_dexec;

//-------prototype-------
//ft_exec_get_path
int		ft_get_envpaths(char **envp, t_dexec *dexec);
int		ft_get_cmdpath(char *cmd, t_dexec *dexec);
//ft_exec_check_path
int		check_cmdpath(t_dexec *dexec);
int 	cmd_cant_use(char *cmd, t_dexec *dexec, int flag);
//ft_free
int		ft_free_exec(char **matrix1, char **matrix2, char *s, int flag_error);
//ft_print_error
int		ft_mes_error(char *message);
int		ft_print_perror(char *original_message);

#endif