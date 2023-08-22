/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:17:56 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/22 14:53:37 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	make_pipe(int *fd_pipe, t_intr *intr, int *fd_in, int *fd_out)
{
	if (intr->flag_pipe > 1)
	{
		if (pipe(fd_pipe) == -1)
			return (perror_wrap("pipe: ", 1));
		intr->pipe = fd_pipe;
		*fd_in = fd_pipe[0];
		*fd_out = fd_pipe[1];
	}
	return (0);
}

static int	scan_simple_cmd(int fd_in, int fd_out, t_ast *node, t_intr intr)
{
	t_dexec	dexec;
	int		status;

	init_dexec(fd_in, fd_out, &dexec, &intr);
	status = scan_btree_io(&dexec, node->left);
	if (status != 0 || node->data == NULL)
		return (end_with_fd_close(&dexec, status));
	if (fd_out == dexec.fd_out && fd_out != STDOUT_FILENO)
		dexec.flag_pipe_close = 1;
	status = scan_environment(node);
	if (status == 1 && node->right != NULL)
		node = node->right;
	else if (status == 1)
		return (end_with_fd_close(&dexec, 0));
	status = scan_path_prog(&dexec, node);
	if (status != 0)
	{
		free_null((void **)&(dexec.cmd_path));
		return (end_with_fd_close(&dexec, status));
	}
	status = exec_do(&dexec, node, intr.flag_wait);
	free_null((void **)&(dexec.cmd_path));
	free_null((void **)&(dexec.cmd_opts));
	return (status);
}

static int	scan_btree_pipe(int *fd_in, int fd_out, t_ast *node, t_intr intr)
{
	int	fd_pipe[2];
	int	status;
	int	fd_in_changed;

	fd_in_changed = *fd_in;
	if (node->data != NULL && node->data->type == PIPE)
	{
		scan_btree_pipe(&fd_in_changed, fd_out, node->left,
			(t_intr){NULL, intr.flag_wait + 2, intr.flag_pipe + 2});
		status = scan_btree_pipe(&fd_in_changed, fd_out, node->right,
				(t_intr){NULL, intr.flag_wait + 1, intr.flag_pipe + 1});
		if (intr.flag_pipe > 1)
			*fd_in = fd_in_changed;
	}
	else
	{
		if (make_pipe(fd_pipe, &intr, fd_in, &fd_out) != 0)
			return (1);
		status = scan_simple_cmd(fd_in_changed, fd_out, node, intr);
	}
	return (status);
}

int	execute_ast(t_ast *ast)
{
	int		val;
	t_intr	intr;
	int		std_in;

	std_in = 0;
	if (sig_forwarding_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	intr = (t_intr){NULL, 0, 0};
	val = scan_btree_pipe(&std_in, STDOUT_FILENO, ast, intr);
	while (wait(NULL) > 0)
		;
	if (sig_interactive_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	return (val);
}
