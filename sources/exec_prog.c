/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:01:43 by hotph             #+#    #+#             */
/*   Updated: 2023/08/13 21:21:28 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	path_is_builtin(char *prog, t_dexec *dexec)
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
}

static int	joint_path(char *path, char *prog, t_dexec *dexec)
{
	if (prog == NULL)
		return (directory_is(path));
	else if (ft_strncmp(path, "./", 2) == 0)
		dexec->cmd_path = ft_strjoin(path, prog);
	else
		dexec->cmd_path = ft_strjoin(path, prog);
	if (dexec->cmd_path == NULL)
		return (ft_mes_error("Error. Fail allocate memory.\n"));
	return (0);
}

static int	get_fullpath(char *path, char *prog, t_dexec *dexec)
{
	int	status;

	if (path != NULL)
	{
		status = joint_path(path, prog, dexec);
		if (status != 0)
			return (status);
	}
	else
	{
		path_is_builtin(prog, dexec);
		status = path_is_envp(prog, dexec);
		free_splited_str(dexec->matrix_envpath);
		if (status == CMD_NOTFOUND)
			return (minishell_error(prog, CMD_NOTFOUND, "command not found"));
		if (status == 1)
			return (status);
	}
	status = check_cmdpath_hub(dexec, prog);
	if (status != 0)
		free_null((void **)&(dexec->cmd_path));
	return (status);
}

int	scan_path_prog(t_dexec *dexec, t_ast *node)
{
	char	*path;
	char	*prog;
	int		status;

	if (node->data != NULL && node->data->type == TEXT)
	{
		path = get_cmd_path(node);
		prog = get_cmd_prog(node);
		if (path == NULL && prog == NULL)
			return (ft_mes_error("Error. Fail to allocate memory.\n"));
		status = get_fullpath(path, prog, dexec);
		free_null((void **)&(path));
		free_null((void **)&(prog));
		if (status != 0)
			return (status);
		dexec->cmd_opts = get_argv(node);
		if (dexec->cmd_opts == NULL)
			return (ft_mes_error("Error. Fail to allocate memory.\n"));
	}
	return (0);
}
