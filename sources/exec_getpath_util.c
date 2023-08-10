/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_getpath_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:46 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/10 15:24:08 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

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
		free(dexec->cmd_path);
		return (minishell_error(prog, CMD_NOTFOUND, "command not found"));
	}
	if (check_cmdpath(dexec->cmd_path, ACCESS_XOK) == 1)
	{
		free(dexec->cmd_path);
		return (minishell_error(prog, CMD_CANT_EXEC, NULL));
	}
	return (0);
}

char	**ft_split_by_token(char **matrix, char token)
{
	size_t	i;
	char	*tmp;

	tmp = get_env("PATH");
	if (tmp == NULL)
	{
		ft_mes_error("Error: 'PATH' not found.\n");
		return (NULL);
	}
	matrix = ft_split(tmp, token);
	if (matrix == NULL)
	{
		free(tmp);
		ft_mes_error("Error. Fail allocate memory.\n");
		return (NULL);
	}
	free(tmp);
	return (matrix);
}
