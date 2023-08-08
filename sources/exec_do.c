/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/08 14:57:57 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

static int	ft_exec_set_redirect(t_dexec *dexec)
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

static void	ft_exec_do_cmd(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		if (errno == EISDIR)
			minishell_error(cmd_path, IS_A_DIRECTORY, NULL);
		else
			perror("minishell");
		exit(1);
	}
}

int	ft_exec_forked(t_dexec *dexec, t_ast *node)
{
	if (node->left != NULL)
		scan_btree_fd(dexec, node->left);
	ft_exec_set_redirect(dexec);
	if (node->data->type == TEXT && node->data->data != NULL)
	{
		dexec->matrix_envpath = ft_split_by_token(dexec->matrix_envpath, ':');
		dexec->cmd_path = ft_get_cmdpath(get_cmd_path(node),get_cmd_prog(node), dexec);
		dexec->cmd_opts = get_argv(node);
		ft_exec_do_cmd(dexec->cmd_path, dexec->cmd_opts, get_envp());
	}
	return (0);
}
