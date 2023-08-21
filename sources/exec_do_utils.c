/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:00:18 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/21 17:13:12 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	with_redirect(t_dexec *dexec, t_ast *node)
{
	int	status;
	int	copy_stdout;

	if (dexec->fd_out != 1 && dexec->flag_pipe == 0)
	{
		copy_stdout = dup(STDOUT_FILENO);
		status = set_redirect(dexec);
		if (status != 0)
			return (0);
	}
	if (dexec->flag_builtin == BUILTIN_ECHO)
		status = built_in_echo(dexec);
	else if (dexec->flag_builtin == BUILTIN_PWD)
		status = built_in_pwd(dexec);
	else if (dexec->flag_builtin == BUILTIN_EXPORT)
		status = built_in_export(arrstr_len(dexec->cmd_opts), dexec->cmd_opts);
	else if (dexec->flag_builtin == BUILTIN_ENV)
		status = built_in_env(arrstr_len(dexec->cmd_opts), dexec->cmd_opts);
	if (dexec->fd_out > 2 && dexec->flag_pipe == 0)
	{
		if (dup2(copy_stdout, STDOUT_FILENO) == -1
			|| close(copy_stdout) == -1)
			return (perror_wrap("dup2/close: ", 1));
	}
	return (status);
}

int	is_builtin(t_dexec *dexec, t_ast *node)
{
	if (dexec->flag_builtin == BUILTIN_ECHO
		|| dexec->flag_builtin == BUILTIN_PWD
		|| dexec->flag_builtin == BUILTIN_ENV
		|| dexec->flag_builtin == BUILTIN_EXPORT)
		return (with_redirect(dexec, node));
	else if (dexec->flag_builtin == BUILTIN_CD)
		return (built_in_cd(dexec));
	if (dexec->flag_builtin == BUILTIN_UNSET)
		return (built_in_unset(arrstr_len(dexec->cmd_opts), dexec->cmd_opts));
	else if (dexec->flag_builtin == BUILTIN_EXIT)
		return (built_in_exit(dexec, node));
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

int	set_redirect(t_dexec *dexec)
{
	if (dexec->fd_in != STDIN_FILENO && dexec->flag_builtin < 0)
	{
		if (dup2(dexec->fd_in, STDIN_FILENO) == -1)
			return (perror_wrap("set_redirect dup2", 1));
		if (close(dexec->fd_in) == -1)
			return (perror_wrap("set_redirect close", 1));
	}
	if (dexec->fd_out != STDOUT_FILENO)
	{
		if (dup2(dexec->fd_out, STDOUT_FILENO) == -1)
			return (perror_wrap("set_redirect dup2", 1));
		if (close(dexec->fd_out) == -1)
			return (perror_wrap("set_redirect close1", 1));
		if (dexec->flag_pipe_close == 1)
		{
			if (close(dexec->pipe[0]) == -1)
				return (perror_wrap("set_redirect close2", 1));
		}
	}
	return (0);
}
