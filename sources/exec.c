/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:54:41 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/14 15:34:48 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_dexec(int fd_in, int fd_out, t_dexec *dexec)
{
	dexec->matrix_envpath = NULL;
	dexec->cmd_path = NULL;
	dexec->cmd_opts = NULL;
	dexec->fd_in = fd_in;
	dexec->fd_out = fd_out;
}

static int	scan_simple_cmd(int fd_in, int fd_out, t_ast *node, int flag)
{
	t_dexec	dexec;
	int		status;

	init_dexec(fd_in, fd_out, &dexec);
	status = scan_btree_io(&dexec, node->left);
	if (status != 0)
		return (status);
	if (node->data == NULL)
		return (0);
	status = scan_path_prog(&dexec, node);
	if (status != 0)
	{
		free_null((void **)&(dexec.cmd_path));
		return (status);
	}
	status = exec_do(&dexec, node, flag);
	free_null((void **)&(dexec.cmd_path));
	free_null((void **)&(dexec.cmd_opts));
	return (status);
}

static int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node, int flag)
{
	int	fd_pipe[2];
	int	status;

	if (node->data != NULL && node->data->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
			return (perror_wrap("scan_pipe", 1));
		scan_btree_pipe(fd_in, fd_pipe[1], node->left, flag + 2);
		status = scan_btree_pipe(fd_pipe[0], fd_out, node->right, flag + 1);
	}
	else
		status = scan_simple_cmd(fd_in, fd_out, node, flag);
	return (status);
}

void	execute_ast(t_ast *ast)
{
	int	val;

	val = scan_btree_pipe(STDIN_FILENO, STDOUT_FILENO, ast, 0);
	while (wait(NULL) > 0)
		;
}
