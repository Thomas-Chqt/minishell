/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/03 11:57:03 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_exec_do_cmd(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		if (errno == EISDIR)
			cmd_cant_use(cmd_path, CMD_SIMPLE);
		exit(1);
	}
}

int	ft_exec_forked(t_dexec *dexec, t_tree *node)
{
	if (node->left != NULL)
		scan_btree_fd(dexec, node->left);
	if (node->type == NODE_CMD)
	{
		dexec.cmd_opts = //joint cmd & opts to char** matrix, end with NULL;
		if (dexec.cmd_opts == NULL)
			exit(ft_mes_error("Error. Fail allocate memory.\n"));
		dexec.matrix_envpath =  ft_split_by_token(dexec.matrix_envpath, ':');
		dexec.cmd_path = ft_get_cmdpath(path, prog, &dexec);
		ft_exec_do_cmd(dexec.cmd_path, cmd_opts, envp);
	}
	return (0);
}
