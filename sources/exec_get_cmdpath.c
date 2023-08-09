/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_cmdpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/09 17:41:04 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static int	path_is_envp(char *cmd, t_dexec *dexec)
{
	size_t	i;

	i = 0;
	dexec->matrix_envpath = ft_split_by_token(dexec->matrix_envpath, ':');
	if (dexec->matrix_envpath == NULL)
		return (1);
	while (dexec->matrix_envpath[i] != NULL)
	{
		if (make_potential_path(dexec, dexec->matrix_envpath[i++], cmd) != 0)
			return (1);
		if (check_cmdpath(dexec->cmd_path, ACCESS_FOK) == 0)
			return (0);
		free(dexec->cmd_path);
	}
	return (CMD_NOTFOUND);
}

static int	path_is(char *path)
{
	int		exit_val;

	if (ft_stat_wrap(path, STAT_ISDIR) == true)
		exit_val = minishell_error(path, CMD_CANT_EXEC, "is a directory");
	else if (ft_stat_wrap(path, STAT_ISREG) == true)
		exit_val = minishell_error(path, CMD_CANT_EXEC, "Not a directory");
	else if (check_cmdpath(path, ACCESS_FOK) == 1)
		exit_val = minishell_error(path, CMD_NOTFOUND, NULL);
	return (exit_val);
}

static void	path_is_builtin(char *prog, t_dexec *dexec)
{
	if (str_cmp("echo", prog) == 0)
		;
	if (str_cmp("cd", prog) == 0)
		;
	if (str_cmp("pwd", prog) == 0)
		;
	if (str_cmp("export", prog) == 0)
		;
	if (str_cmp("unset", prog) == 0)
		;
	if (str_cmp("env", prog) == 0)
		;
	if (str_cmp("exit", prog) == 0)
		;
}

int	ft_get_cmdpath(char *path, char *prog, t_dexec *dexec)
{
	int	exit_val;

	if (path != NULL)
	{
		if (prog == NULL)
			return (path_is(path));
		else if (ft_strncmp(path, "./", 2) == 0)
			dexec->cmd_path = ft_strjoin(&path[2], prog);
		else
			dexec->cmd_path = ft_strjoin(path, prog);
		if (dexec->cmd_path == NULL)
			return (ft_mes_error("Error. Fail allocate memory.\n"));
	}
	else
	{
		path_is_builtin(prog, dexec);
		exit_val = path_is_envp(prog, dexec);
		if (exit_val == CMD_NOTFOUND)
			return (minishell_error(prog, CMD_NOTFOUND, "command not found"));
		if (exit_val == 1)
			return (exit_val);
	}
	exit_val = check_cmdpath_hub(dexec, prog);
	return (exit_val);
}
