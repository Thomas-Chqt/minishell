/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/16 15:13:53 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	built_in_cd(t_dexec *dexec)
{
	if (dexec->cmd_opts[1] == NULL)
	{
		if (chdir("/") != 0)
		{
			perror("minishell: cd: ");
			return (EX_FILE_OPEN_ERR);
		}
	}
	else if (chdir(dexec->cmd_opts[1]) != 0)
	{
		if (ft_access_wrap(dexec->cmd_opts[1], ACCESS_FOK) == false)
			printf_error_msg("minishell: cd: %: No such file or directory",
				(dexec->cmd_opts + 1), 1);
		else if (ft_stat_wrap(dexec->cmd_opts[1], STAT_ISDIR) == false)
			printf_error_msg("minishell: cd: %: Not a directory",
				(dexec->cmd_opts + 1), 1);
		else if (ft_access_wrap(dexec->cmd_opts[1], ACCESS_XOK) == false)
			printf_error_msg("minishell: cd: %: Permission denied",
				(dexec->cmd_opts + 1), 1);
		return (EX_FILE_OPEN_ERR);
	}
	return (0);
}
