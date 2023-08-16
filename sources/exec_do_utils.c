/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:00:18 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/16 15:23:20 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_builtin(t_dexec *dexec)
{
	// if (dexec->flag_builtin == BUILTIN_ECHO)
	// 	return (built_in_echo(dexec));
	if (dexec->flag_builtin == BUILTIN_CD)
		return (built_in_cd(dexec));
	// if (dexec->flag_builtin == BUILTIN_PWD)
	// 	return (built_in_pwd());
	// if (dexec->flag_builtin == BUILTIN_EXPORT)
	// 	return (built_in_export(dexec));
	// if (dexec->flag_builtin == BUILTIN_UNSET)
	// 	return (built_in_unset(dexec));
	// if (dexec->flag_builtin == BUILTIN_ENV)
	// 	return (built_in_env(dexec));
	// if (dexec->flag_builtin == BUILTIN_EXIT)
	// 	return (built_in_exit(dexec));
}
