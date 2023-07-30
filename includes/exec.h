/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:34:04 by sotanaka          #+#    #+#             */
/*   Updated: 2023/07/30 19:12:42 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//-------include-------
# include <minishell.h>
// # include <unistd.h>
// # include <stdlib.h>

//-------typedef-------
typedef struct s_dexec
{
	char	**matrix_envpath;
	char	*cmd_path;
	char	**cmd_opts;
}	t_dexec;

//-------prototype-------
//ft_get_abs_path
int		ft_get_envpaths(char **envp, t_dexec *dexec);
int		ft_get_cmdpath(char *cmd, t_dexec *dexec);

//ft_free
int		ft_free_exec(char **matrix1, char **matrix2, char *s, int flag_error);
//ft_print_error
int		ft_mes_error(char *message);
int		ft_print_perror(char *original_message);

#endif