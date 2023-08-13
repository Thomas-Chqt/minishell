/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/13 21:24:55 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

static char	**split_wrap(char **matrix, char token)
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

static int	make_potential_path(t_dexec *dexec, char *envpath, char *cmd)
{
	char	*pre_path;

	pre_path = ft_strjoin(envpath, "/");
	if (pre_path == NULL)
		return (ft_mes_error("Error. Fail allocate memory.\n"));
	dexec->cmd_path = ft_strjoin(pre_path, cmd);
	if (dexec->cmd_path == NULL)
	{
		free(pre_path);
		return (ft_mes_error("Error. Fail allocate memory.\n"));
	}
	free(pre_path);
	return (0);
}

int	path_is_envp(char *cmd, t_dexec *dexec)
{
	size_t	i;

	i = 0;
	dexec->matrix_envpath = split_wrap(dexec->matrix_envpath, ':');
	if (dexec->matrix_envpath == NULL)
		return (1);
	while (dexec->matrix_envpath[i] != NULL)
	{
		if (make_potential_path(dexec, dexec->matrix_envpath[i++], cmd) != 0)
			return (1);
		if (check_cmdpath(dexec->cmd_path, ACCESS_FOK) == 0)
			return (0);
		free_null((void **)&(dexec->cmd_path));
	}
	return (CMD_NOTFOUND);
}

int	directory_is(char *path)
{
	int		status;
	char	*cpy;

	cpy = ft_strdup(path);
	if (cpy == NULL)
		return (ft_mes_error("Error. Fail allocate memory.\n"));
	path[ft_strlen(path) - 1] = '\0';
	if (ft_stat_wrap(path, STAT_ISDIR) == true)
		status = minishell_error(cpy, CMD_CANT_EXEC, "Is a directory");
	else if (ft_stat_wrap(path, STAT_ISREG) == true)
		status = minishell_error(cpy, CMD_CANT_EXEC, "Not a directory");
	else if (ft_stat_wrap(path, 0) == 255)
		status = 255;
	else if (check_cmdpath(path, ACCESS_FOK) == 1)
		status = minishell_error(cpy, CMD_NOTFOUND, NULL);
	free(cpy);
	return (status);
}
