/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:46 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/28 16:38:59 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_stat_wrap(char *path, int flag)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
	{
		perror_wrap("stat", 1);
		return (1);
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
			printf_error_msg("%s: %s",
				(char *[2]){cmd_path, strerror(errno)}, CMD_SIMPLE);
		else
			return (0);
	}
	return (1);
}

int	check_cmdpath_hub(t_exe *exe)
{
	if (check_cmdpath(exe->cmd_path, ACCESS_FOK) == 1)
		return (printf_error_msg("%s: No such file or directory",
				&exe->cmd_path, CMD_NOTFOUND));
	if (ft_stat_wrap(exe->cmd_path, STAT_ISDIR) == true)
		return (printf_error_msg("%s: Is a directory",
				&exe->cmd_path, CMD_CANT_EXEC));
	if (check_cmdpath(exe->cmd_path, ACCESS_XOK) == 1)
		return (printf_error_msg("%s: %s",
				(char *[2]){exe->cmd_path, strerror(errno)}, CMD_CANT_EXEC));
	return (0);
}
