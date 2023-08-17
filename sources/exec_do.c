/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/17 14:09:42 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "builtin.h"

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

static int	do_cmd(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		free_splited_str(envp);
		if (errno == EISDIR)
			return (exec_error(cmd_path, IS_A_DIRECTORY, NULL));
		else
			perror("minishell");
	}
	return (1);
}

static int	set_redirect(t_dexec *dexec)
{
	if (dexec->fd_in != STDIN_FILENO)
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
		if (dexec->flag_pipe == 1)
		{
			if (close(dexec->pipe[0]) == -1)
				return (perror_wrap("set_redirect close2", 1));
		}
			return (perror_wrap("set_redirect close1", 1));
		if (dexec->flag_pipe == 1)
		{
			if (close(dexec->pipe[0]) == -1)
				return (perror_wrap("set_redirect close2", 1));
		}
	}
	return (0);
}

void	forked(t_dexec *dexec, t_ast *node)
{
	int		exit_val;

	exit_val = set_redirect(dexec);
	if (exit_val != 0)
		exit(exit_val);
	if (node->data != NULL && node->data->type == TEXT)
	{
		exit_val = do_cmd(dexec->cmd_path, dexec->cmd_opts, get_envp());
		if (exit_val != 0)
		{
			free(dexec->cmd_path);
			free(dexec->cmd_opts);
			exit(exit_val);
		}
	}
	exit(exit_val);
}

int	exec_do(t_dexec *dexec, t_ast *node, int flag)
{
	int		pid;
	int		status;

	if (dexec->flag_builtin > 0)
		return (is_builtin(dexec));
	pid = fork();
	if (pid == -1)
		return (perror_wrap("exec_do fork", 1));
	else if (pid == 0)
		forked(dexec, node);
	else
	{
		status = fd_close(dexec->fd_in, dexec->fd_out);
		if (status != 0)
			return (perror_wrap("exec_do fd_close", 1));
		if (flag <= 1)
		{
			if (waitpid(pid, &status, 0) == -1)
				return (perror_wrap("exec_do waitpid", 1));
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}
	return (status);
}
