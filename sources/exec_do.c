/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/23 09:48:59 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "environment.h"
#include "builtin.h"

static int	is_standard(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		free_splited_str(envp);
		if (errno == EISDIR)
			return (printf_error_msg("minishell: %: %",
					(char *[2]){cmd_path, strerror(errno)}, IS_A_DIRECTORY));
		else
			printf_error_msg("minishell: %: %",
				(char *[2]){cmd_path, strerror(errno)}, 0);
	}
	return (1);
}

static void	at_child(t_exe *exe, t_ast *node)
{
	int		exit_val;

	exit_val = set_redirect(exe);
	if (exit_val != 0)
		exit(exit_val);
	if (node->data != NULL && node->data->type == TEXT)
	{
		if (exe->flag_builtin > 0)
			exit_val = is_builtin(exe, node);
		else
			exit_val = is_standard(exe->cmd_path, exe->cmd_opts,
					get_envp());
	}
	exit(exit_val);
}

static int	at_parent(t_exe *exe, int pid, int flag)
{
	int	status;

	status = fd_close(exe->fd_in, exe->fd_out);
	if (status != 0)
		return (perror_wrap("at_parent fd_close", 1));
	if (flag <= 1)
	{
		if (waitpid(pid, &status, 0) == -1)
			return (perror_wrap("at_parant waitpid", 1));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}

int	exec_do(t_exe *exe, t_ast *node, int flag)
{
	int		pid;
	int		status;

	pid = 0;
	status = 0;
	if (exe->flag_pipe == 0 && exe->flag_builtin > 0)
		status = is_builtin(exe, node);
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror_wrap("exec_do fork", 1));
		else if (pid == 0)
			at_child(exe, node);
	}
	if (pid > 0)
		status = at_parent(exe, pid, flag);
	return (status);
}
