/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_get_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/07/30 19:48:28 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_cmdpath(t_dexec *dexec)
{
	errno = 0;
	if (access(dexec->cmd_path, X_OK) == 0)
		return (0);
	else if (errno == EACCES)
	{
		ft_print_perror(dexec->cmd_path);
		return (ft_free_exec(dexec->matrix_envpath, NULL, dexec->cmd_path, 0));
	}
	return (-1);
}

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
	return (EXIT_SUCCESS);
}

int cmd_not_found(char *cmd, t_dexec *dexec)//kaizen. accept type permission denied
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(cmd, ": command not found\n");
	if (tmp1 == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, NULL, 1));
	tmp2 = ft_strjoin("minishell: ", tmp1);
	if (tmp2 == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, tmp1, 1));
	free(tmp1);
	ft_mes_error(tmp2);
	return (ft_free_exec(dexec->matrix_envpath, NULL, tmp2, 0));
}

int	ft_get_cmdpath(char *cmd, t_dexec *dexec)
{
	size_t	i;
	int		flag;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL)
	{
		dexec->cmd_path = ft_strdup(cmd);
		if (dexec->cmd_path == NULL)
			return (ft_free_exec(dexec->matrix_envpath, NULL, NULL, 0));
		flag = check_cmdpath(dexec);
		if (flag == 0 || flag == 1)
			return (flag);
		free(dexec->cmd_path);
	}
	else
	{
		while (dexec->matrix_envpath[i] != NULL)
		{
			if (make_potential_fullpath(dexec, dexec->matrix_envpath[i++], cmd) != 0)
				return (1);
			flag = check_cmdpath(dexec);
			if (flag == 0 || flag == 1)
				return (flag);
			free(dexec->cmd_path);
		}
	}
	return (cmd_not_found(cmd, dexec));
}

int	ft_get_envpaths(char **envp, t_dexec *dexec)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			dexec->matrix_envpath = ft_split(&envp[i][5], ':');
			if (dexec->matrix_envpath == NULL)
				return (ft_free_exec(NULL, NULL, NULL, 1));
			return (0);
		}
		i++;
	}
	ft_mes_error("Error: PATH= not found.");
	return (1);
}
