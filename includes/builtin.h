/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:23:23 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/21 14:10:40 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//-------include-------
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
int		built_in_echo(t_dexec *dexec);
int		built_in_cd(t_dexec *dexec);
int		built_in_pwd(t_dexec *dexec);
int		built_in_export(int argc, char *argv[]);
int		built_in_unset(int argc, char *argv[]);
int		built_in_env(int argc, char *argv[]);
int		built_in_exit(t_dexec *dexec, t_ast *node);
int		is_builtin(t_dexec *dexec, t_ast *node);

#endif