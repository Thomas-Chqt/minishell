/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/03 18:01:00 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static int	ft_exec_do_cmd(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		if (errno == EISDIR)
			cmd_cant_use(cmd_path, IS_A_DIRECTORY);
		else
			perror("minishell");
		exit(1);
	}
}

int	ft_exec_forked(t_dexec *dexec, t_ast *node)
{
	char **envp;//for debug
	if (node->left != NULL)
		scan_btree_fd(dexec, node->left);
	ft_exec_set_redirect(dexec);
	if (node->data->type == TEXT && node->data->data != NULL)
	{
		//Get data of cmd_path, cmd_opts, envp is not available.
		ft_exec_do_cmd(dexec->cmd_path, dexec->cmd_opts, envp);
	}
	return (0);
}
