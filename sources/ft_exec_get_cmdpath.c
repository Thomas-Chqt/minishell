/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_get_cmdpath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 18:15:38 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	make_potential_fullpath(t_dexec *dexec, char *envpath, char *cmd)
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
		if (make_potential_fullpath(dexec, dexec->matrix_envpath[i++], cmd) != 0)
			exit (1);
		flag = check_cmdpath(dexec->cmd_path, ACCESS_FOK);
		if (flag == 0)
			return (0);
		free(dexec->cmd_path);
	}
	return (1);
}

char	*ft_get_cmdpath(char *path, char *prog, t_dexec *dexec)
{
	int		result;

	if (ft_strncmp(path, "./", 2) == 0)
		dexec->cmd_path = ft_strjoin(path[1], prog);
	else if (path != NULL)
		dexec->cmd_path = ft_strjoin(path, prog);
	if (dexec->cmd_path == NULL)
		exit(ft_mes_error("Error. Fail allocate memory.\n"));
	if (path == NULL)
	{
		if (path_is_envp(prog, dexec) == 1)
			cmd_cant_use(prog, CMD_NOTFOUND);
	}
	result = check_cmdpath(dexec->cmd_path, ACCESS_FOK);
	if (result == 1)
		cmd_cant_use(prog, CMD_NOTFOUND);
	result = check_cmdpath(dexec->cmd_path, ACCESS_XOK);
	if (result == 1)
		cmd_cant_use(prog, CMD_PERM_DENIED);
	result = check_cmdpath(dexec->cmd_path, STAT_ISDIR);
	return (dexec->cmd_path);
}
