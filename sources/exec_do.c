/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/10 15:18:42 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

static int	exec_set_redirect(t_dexec *dexec)
{
	if (dexec->fd_in != STDIN_FILENO)
	{
		if (dup2(dexec->fd_in, STDIN_FILENO) == -1)
			exit(ft_print_perror("Error. Fail to dup2_fd_in.\n"));
		if (close(dexec->fd_in) == -1)
			exit(ft_print_perror("Error. Fail to close_fd_in.\n"));
	}
	if (dexec->fd_out != STDOUT_FILENO)
	{
		if (dup2(dexec->fd_out, STDOUT_FILENO) == -1)
			exit(ft_print_perror("Error. Fail to dup2_fd_out.\n"));
		if (close(dexec->fd_out) == -1)
			exit(ft_print_perror("Error. Fail to close_fd_out.\n"));
	}
	return (0);
}

static int	exec_do_cmd(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		free_splited_str(envp);
		if (errno == EISDIR)
			return (minishell_error(cmd_path, IS_A_DIRECTORY, NULL));
		else
			perror("minishell");
	}
	return (1);
}

static int	preset_and_do(t_dexec *dexec, t_ast *node, char *path, char *prog)
{
	int	exit_val;

	exit_val = ft_get_cmdpath(path, prog, dexec);
	if (exit_val != 0)
		return (exit_val);
	dexec->cmd_opts = get_argv(node);
	if (dexec->cmd_opts == NULL)
	{
		free(dexec->cmd_path);
		return (ft_mes_error("Error. Fail to allocate memory.\n"));
	}
	exit_val = exec_do_cmd(dexec->cmd_path, dexec->cmd_opts, get_envp());
	if (exit_val != 0)
	{
		free(dexec->cmd_path);
		free(dexec->cmd_opts);
		return (exit_val);
	}
	return (0);
}

void	ft_exec_forked(t_dexec *dexec, t_ast *node)
{
	char	*path;
	char	*prog;
	int		exit_val;

	exit_val = 0;
	scan_btree_fd(dexec, node->left);
	exec_set_redirect(dexec);
	if (node->data != NULL && node->data->type == TEXT)
	{
		path = get_cmd_path(node);
		prog = get_cmd_prog(node);
		if (path == NULL && prog == NULL)
			exit(ft_mes_error("Error. Fail to allocate memory.\n"));
		exit_val = preset_and_do(dexec, node, path, prog);
		free(path);
		free(prog);
	}
	exit (exit_val);
}
