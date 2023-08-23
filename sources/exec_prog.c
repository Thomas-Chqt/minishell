/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:01:43 by hotph             #+#    #+#             */
/*   Updated: 2023/08/23 09:49:03 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

int	path_is_builtin(char *path, char *prog, t_exe *exe)
{
	if (path != NULL)
		return (1);
	if (str_cmp("echo", prog) == 0)
		exe->flag_builtin = BUILTIN_ECHO;
	if (str_cmp("cd", prog) == 0)
		exe->flag_builtin = BUILTIN_CD;
	if (str_cmp("pwd", prog) == 0)
		exe->flag_builtin = BUILTIN_PWD;
	if (str_cmp("export", prog) == 0)
		exe->flag_builtin = BUILTIN_EXPORT;
	if (str_cmp("unset", prog) == 0)
		exe->flag_builtin = BUILTIN_UNSET;
	if (str_cmp("env", prog) == 0)
		exe->flag_builtin = BUILTIN_ENV;
	if (str_cmp("exit", prog) == 0)
		exe->flag_builtin = BUILTIN_EXIT;
	if (exe->flag_builtin == -1)
		return (1);
	else
	{
		exe->cmd_path = ft_strdup(prog);
		if (exe->cmd_path == NULL)
			return (print_error(MALLOC_ERROR));
	}
	return (0);
}

static int	joint_path(char *path, char *prog, t_exe *exe)
{
	if (prog == NULL)
		return (directory_is(path));
	else if (ft_strncmp(path, "./", 2) == 0)
		exe->cmd_path = ft_strjoin(path, prog);
	else
		exe->cmd_path = ft_strjoin(path, prog);
	if (exe->cmd_path == NULL)
		return (print_error(MALLOC_ERROR));
	return (0);
}

static int	get_fullpath(char *path, char *prog, t_exe *exe)
{
	int	status;

	status = path_is_builtin(path, prog, exe);
	if (status == 0)
		return (status);
	else if (path != NULL)
		status = joint_path(path, prog, exe);
	else
	{
		status = path_is_envp(prog, exe);
		free_splited_str(exe->matrix_envpath);
		if (status == CMD_NOTFOUND)
			printf_error_msg("minishell: %: command not found",
				&prog, CMD_NOTFOUND);
	}
	if (status != 0)
		return (status);
	status = check_cmdpath_hub(exe, prog);
	if (status != 0)
		free_null((void **)&(exe->cmd_path));
	return (status);
}

int	scan_path_prog(t_exe *exe, t_ast *node)
{
	char	*path;
	char	*prog;
	int		status;
	int		error;

	if (node->data != NULL && node->data->type == TEXT)
	{
		path = get_cmd_path(node, &error);
		if (path == NULL && error == MALLOC_ERROR)
			return (print_error(MALLOC_ERROR));
		prog = get_cmd_prog(node, &error);
		if (prog == NULL && error == MALLOC_ERROR)
			return (print_error(MALLOC_ERROR));
		status = get_fullpath(path, prog, exe);
		free_null((void **)&(path));
		free_null((void **)&(prog));
		if (status != 0)
			return (status);
		exe->cmd_opts = get_argv(node);
		if (exe->cmd_opts == NULL)
			return (print_error(MALLOC_ERROR));
	}
	return (0);
}
