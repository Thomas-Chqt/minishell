/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_cmdpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/04 18:05:41 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_cmdpath(char *cmd_path, int flag)
{
	int			err;

	errno = 0;
	if (flag == ACCESS_FOK)
	{
		err = ft_access_wrap(cmd_path, F_OK);
		if (err == true)
			return (0);
	}
	else if (flag == ACCESS_XOK)
	{
		err = ft_access_wrap(cmd_path, X_OK);
		if (err == false)
			minishell_error(cmd_path, CMD_SIMPLE, NULL);
		else
			return (0);
	}
	return (1);
}

static int	make_potential_path(t_dexec *dexec, char *envpath, char *cmd)
{
	char	*pre_path;

	pre_path = ft_strjoin(envpath, "/");
	if (pre_path == NULL)
		exit (ft_mes_error("Error. Fail allocate memory.\n"));
	dexec->cmd_path = ft_strjoin(pre_path, cmd);
	if (dexec->cmd_path == NULL)
		exit (ft_mes_error("Error. Fail allocate memory.\n"));
	free(pre_path);
	return (0);
}

static int	path_is_envp(char *cmd, t_dexec *dexec)
{
	size_t	i;
	int		flag;

	while (dexec->matrix_envpath[i] != NULL)
	{
		if (make_potential_path(dexec, dexec->matrix_envpath[i++], cmd) != 0)
			exit (1);
		flag = check_cmdpath(dexec->cmd_path, ACCESS_FOK);
		if (flag == 0)
			return (0);
		free(dexec->cmd_path);
	}
	return (1);
}

static void	path_is(char *path)
{
	if (ft_stat_wrap(path, STAT_ISDIR) == true)
		minishell_error(path, CMD_CANT_EXEC, "is a directory");
	else if (ft_stat_wrap(path, STAT_ISREG) == true)
		minishell_error(path, CMD_CANT_EXEC, "Not a directory");
	else if (check_cmdpath(path, ACCESS_FOK) == 1)
		minishell_error(path, CMD_NOTFOUND, NULL);
	exit(1);
}

char	*ft_get_cmdpath(char *path, char *prog, t_dexec *dexec)
{
	int		result;

	if (path != NULL && prog == NULL)
		path_is(path);
	else if (ft_strncmp(path, "./", 2) == 0)
		dexec->cmd_path = ft_strjoin(path[1], prog);
	else if (path != NULL)
		dexec->cmd_path = ft_strjoin(path, prog);
	if (dexec->cmd_path == NULL)
		exit(ft_mes_error("Error. Fail allocate memory.\n"));
	if (path == NULL)
	{
		if (path_is_envp(prog, dexec) == 1)
			minishell_error(prog, CMD_NOTFOUND, "command not found");
	}
	result = check_cmdpath(dexec->cmd_path, ACCESS_FOK);
	if (result == 1)
		minishell_error(prog, CMD_NOTFOUND, "command not found");
	result = check_cmdpath(dexec->cmd_path, ACCESS_XOK);
	if (result == 1)
		minishell_error(prog, CMD_CANT_EXEC, NULL);
	return (dexec->cmd_path);
}
