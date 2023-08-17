/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/17 16:13:41 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_check_path(t_dexec *dexec)
{
	if (ft_access_wrap(dexec->cmd_opts[1], ACCESS_FOK) == false)
		return (printf_error_msg("minishell: cd: %: No such file or directory",
			(dexec->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_stat_wrap(dexec->cmd_opts[1], STAT_ISDIR) == false)
		return (printf_error_msg("minishell: cd: %: Not a directory",
			(dexec->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_access_wrap(dexec->cmd_opts[1], ACCESS_XOK) == false)
		return (printf_error_msg("minishell: cd: %: Permission denied",
			(dexec->cmd_opts + 1), EX_FILE_OPEN_ERR));
	return (0);
}

static int	cd_do_nonfork_or_child(char *path, int flag_pipe)
{
	int		status;

	status = 0;
	if (path == NULL)
	{
		if (chdir("/") != 0)
			status = perror_wrap("minishell: cd: ", 1);
	}
	else if (chdir(path) != 0)
		status = perror_wrap("minishell: cd: ", 1);
	if (flag_pipe == 1)
		exit(status);
	else if (status != 0)
		return (-1);
	return (status);
}

int	built_in_cd(t_dexec *dexec)
{
	int		pid;

	pid = 0;
	if (cd_check_path(dexec) == EX_FILE_OPEN_ERR)
		return (-1);
	if (dexec->flag_pipe == 1)
		pid = fork();
	if (pid == 0)
		return (cd_do_nonfork_or_child(dexec->cmd_opts[1], dexec->flag_pipe));
	else
		return (pid);
}
