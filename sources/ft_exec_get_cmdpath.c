/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_get_cmdpath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 13:22:54 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	make_potential_fullpath(t_dexec *dexec, char *envpath, char *cmd)
{
	char	*pre_path;

	pre_path = ft_strjoin(envpath, "/");
	if (pre_path == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, NULL, 1));
	dexec->cmd_path = ft_strjoin(pre_path, cmd);
	if (dexec->cmd_path == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, pre_path, 1));
	free(pre_path);
	return (0);
}

static int	path_is_current(char *cmd, t_dexec *dexec)
{
	char	path_pwd[255];
	char	*pre_path;
	int		flag;

	if (getcwd(path_pwd, 255) == NULL)
	{
		perror("(f)getcwd: ");
		return (ft_free_exec(NULL, NULL, path_pwd, 0));
	}
	dexec->cmd_path = ft_strjoin(path_pwd, &cmd[1]);
	if (dexec->cmd_path == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, path_pwd, 1));
	flag = check_cmdpath(dexec);
	if (errno == ENOENT)
		exit(cmd_cant_use(cmd, dexec, CMD_SIMPLE));
	if (flag == 0 || flag == 1)
		return (flag);
	return (0);
}

static int	path_is_absolute(char *cmd, t_dexec *dexec)
{
	int		flag;

	dexec->cmd_path = ft_strdup(cmd);
	if (dexec->cmd_path == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, NULL, 0));
	flag = check_cmdpath(dexec);
	if (flag == 0 || flag == 1)
		return (flag);
	free(dexec->cmd_path);
	return (flag);
}

path_is_relative(char *cmd, t_dexec *dexec)
{
	char	*path_pwd;
	int		flag;

	path_pwd = getcwd(NULL, 0);
	if (path_pwd == NULL)
	{
		perror("(f)getcwd: ");
		return (ft_free_exec(NULL, NULL, path_pwd, 0));
	}
	dexec->cmd_path = ft_strjoin(path_pwd, "/");
	if (dexec->cmd_path == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, path_pwd, 1));
	free(path_pwd);
	path_pwd = ft_strjoin(dexec->cmd_path, cmd);
	if (path_pwd == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, dexec->cmd_path, 1));
	free(dexec->cmd_path);
	dexec->cmd_path = path_pwd;
	flag = check_cmdpath(dexec);
	if (flag == 0 || flag == 1)
		return (flag);
	return (0);
}

static int	path_is_envp(char *cmd, t_dexec *dexec)
{
	size_t	i;
	int		flag;

	while (dexec->matrix_envpath[i] != NULL)
	{
		if (make_potential_fullpath(dexec, dexec->matrix_envpath[i++], cmd) != 0)
			return (1);
		flag = check_cmdpath(dexec);
		if (flag == 0 || flag == 1)
			return (flag);
		free(dexec->cmd_path);
	}
	return (1);
}

int	ft_get_cmdpath(char *cmd, t_dexec *dexec)
{
	int	result;

	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		result = path_is_absolute(cmd, dexec);
		if (result == 0 || result == 1)
			return (result);
	}
	else if (ft_strncmp(cmd, "./", 2) == 0)
		result = path_is_current(cmd, dexec);
	else if (ft_strchr(cmd, '/') != NULL)
		result = path_is_relative(cmd, dexec);
	else
		result = path_is_envp(cmd, dexec);
	if (result == 0)
		return (result);
	return (cmd_cant_use(cmd, dexec, CMD_NOTFOUND));
}
