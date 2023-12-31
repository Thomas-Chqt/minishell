/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:23:23 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/02 12:46:40 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//-------include-------
# include "minishell.h"
# include "error.h"
# include "exec.h"
# include "environment.h"

//-------define-------
# define BUILTIN_ECHO 1
# define BUILTIN_CD 2
# define BUILTIN_PWD 3
# define BUILTIN_EXPORT 4
# define BUILTIN_UNSET 5
# define BUILTIN_ENV 6
# define BUILTIN_EXIT 7

//-------prototype-------
int		built_in_echo(t_exe *exe);
//cd utils
void	curtail_str_by_char(char *str, char delim);
int		get_pwd_wrap(char **dest);
int		set_env_key(char *key);
int		cd_via_upper(char *path, int flag_oldpwd);
int		cd_to_path(char *path, int flag_oldpwd);
int		cd_to_current(int flag_oldpwd);
int		cd_to_upper(int oldpwd);
int		built_in_cd(char *path, int flag_pipe, int flag_oldpwd);
int		built_in_pwd(void);
int		built_in_export(int argc, char *argv[]);
int		built_in_unset(int argc, char *argv[]);
int		built_in_env(int argc, char *argv[]);
int		built_in_exit(t_exe *exe, t_ast *node);
int		is_builtin(t_exe *exe, t_ast *node);

#endif