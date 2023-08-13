/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:46 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/13 21:15:56 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_stat_wrap(char *path, int flag)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
	{
		ft_print_perror("stat");
		return (255);
	}
	if (flag == STAT_ISDIR)
	{
		if (S_ISDIR(buf.st_mode))
			return (true);
	}
	else if (flag == STAT_ISREG)
	{
		if (S_ISREG(buf.st_mode))
			return (true);
	}
	return (false);
}

int	ft_access_wrap(char *path, int flag)
{
	errno = 0;
	if (flag == ACCESS_FOK)
	{
		if (access(path, F_OK) == 0)
			return (true);
	}
	else if (flag == ACCESS_ROK)
	{
		if (access(path, R_OK) == 0)
			return (true);
	}
	else if (flag == ACCESS_WOK)
	{
		if (access(path, W_OK) == 0)
			return (true);
	}
	else if (flag == ACCESS_XOK)
	{
		if (access(path, X_OK) == 0)
			return (true);
	}
	return (false);
}

int	check_cmdpath(char *cmd_path, int flag)
{
	int	err;

	errno = 0;
	if (flag == ACCESS_FOK)
	{
		err = ft_access_wrap(cmd_path, ACCESS_FOK);
		if (err == true)
			return (0);
	}
	else if (flag == ACCESS_XOK)
	{
		err = ft_access_wrap(cmd_path, ACCESS_FOK);
		if (err == false)
			minishell_error(cmd_path, CMD_SIMPLE, NULL);
		else
			return (0);
	}
	return (1);
}

int	check_cmdpath_hub(t_dexec *dexec, char *prog)
{
	if (check_cmdpath(dexec->cmd_path, ACCESS_FOK) == 1)
	{
		return (minishell_error(dexec->cmd_path, CMD_NOTFOUND, "command not found"));
	}
	if (ft_stat_wrap(dexec->cmd_path, STAT_ISDIR) == true)
	{
		return (minishell_error(dexec->cmd_path, CMD_CANT_EXEC, "Is a directory"));
	}
	if (check_cmdpath(dexec->cmd_path, ACCESS_XOK) == 1)
	{
		return (minishell_error(dexec->cmd_path, CMD_CANT_EXEC, NULL));
	}
	return (0);
}
