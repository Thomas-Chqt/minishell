/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:23:23 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/17 14:11:43 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//-------include-------
# include "exec.h"

//-------define-------
# define BUILTIN_ECHO 1
# define BUILTIN_CD 2
# define BUILTIN_PWD 3
# define BUILTIN_EXPORT 4
# define BUILTIN_UNSET 5
# define BUILTIN_ENV 6
# define BUILTIN_EXIT 7

//-------prototype-------
// int		built_in_echo(t_dexec *dexec);
int		built_in_cd(t_dexec *dexec);
// int		built_in_pwd(void);
// int		built_in_export(t_dexec *dexec);
// int		built_in_unset(t_dexec *dexec);
// int		built_in_env(t_dexec *dexec);
// int		built_in_exit(t_dexec *dexec);
int		is_builtin(t_dexec *dexec);

#endif