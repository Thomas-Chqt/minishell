/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_getpath_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:46 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/04 17:52:45 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_stat_wrap(char *path, int flag)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		exit(ft_mes_error("Error. Fail to stat.\n"));
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