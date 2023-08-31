/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:00:18 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/30 12:37:36 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	with_redirect(t_exe *exe)
{
	int	status;
	int	copy_stdout;

	if (exe->fd_out != 1 && exe->flag_pipe == 0)
	{
		copy_stdout = dup(STDOUT_FILENO);
		status = set_redirect(exe);
		if (status != 0)
			return (0);
	}
	if (exe->flag_builtin == BUILTIN_ECHO)
		status = built_in_echo(exe);
	else if (exe->flag_builtin == BUILTIN_PWD)
		status = built_in_pwd();
	else if (exe->flag_builtin == BUILTIN_EXPORT)
		status = built_in_export(arrstr_len(exe->cmd_opts), exe->cmd_opts);
	else if (exe->flag_builtin == BUILTIN_ENV)
		status = built_in_env(arrstr_len(exe->cmd_opts), exe->cmd_opts);
	if (exe->fd_out > 2 && exe->flag_pipe == 0)
	{
		if (dup2(copy_stdout, STDOUT_FILENO) == -1
			|| close(copy_stdout) == -1)
			return (perror_wrap("dup2/close: ", 1));
	}
	return (status);
}

int	is_builtin(t_exe *exe, t_ast *node)
{
	if (exe->flag_builtin == BUILTIN_ECHO
		|| exe->flag_builtin == BUILTIN_PWD
		|| exe->flag_builtin == BUILTIN_ENV
		|| exe->flag_builtin == BUILTIN_EXPORT)
		return (with_redirect(exe));
	else if (exe->flag_builtin == BUILTIN_CD)
		return (built_in_cd(exe));
	if (exe->flag_builtin == BUILTIN_UNSET)
		return (built_in_unset(arrstr_len(exe->cmd_opts), exe->cmd_opts));
	else if (exe->flag_builtin == BUILTIN_EXIT)
		return (built_in_exit(exe, node));
	return (0);
}

int	fd_close(int fd_in, int fd_out)
{
	int	status;

	status = 0;
	if (fd_in != STDIN_FILENO)
		status = close(fd_in);
	if (fd_out != STDOUT_FILENO)
		status = close(fd_out);
	return (status);
}

int	set_redirect(t_exe *exe)
{
	if (exe->fd_in != STDIN_FILENO && exe->flag_builtin < 0)
	{
		if (dup2(exe->fd_in, STDIN_FILENO) == -1)
			return (perror_wrap("set_redirect dup2", 1));
		if (close(exe->fd_in) == -1)
			return (perror_wrap("set_redirect close", 1));
	}
	if (exe->fd_out != STDOUT_FILENO)
	{
		if (dup2(exe->fd_out, STDOUT_FILENO) == -1)
			return (perror_wrap("set_redirect dup2", 1));
		if (close(exe->fd_out) == -1)
			return (perror_wrap("set_redirect close1", 1));
		if (exe->flag_pipe_close == 1)
		{
			if (close(exe->pipe[0]) == -1)
				return (perror_wrap("set_redirect close2", 1));
		}
	}
	return (0);
}
