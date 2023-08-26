/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:17:56 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/26 17:06:12 by sotanaka         ###   ########.fr       */
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
	t_exe	exe;
	int		status;

	init_exe(fd_in, fd_out, &exe, &intr);
	status = scan_btree_io(&exe, node->left);
	if (status != 0 || node->data == NULL)
		return (end_with_fd_close(&exe, status));
	if (fd_out == exe.fd_out && fd_out != STDOUT_FILENO)
		exe.flag_pipe_close = 1;
	status = skip_if_environment(&node);
	if (status != true)
		return (end_with_fd_close(&exe, status));
	status = scan_path_prog(&exe, node);
	if (status != 0)
	{
		free_null((void **)&(exe.cmd_path));
		return (end_with_fd_close(&exe, status));
	}
	status = exec_do(&exe, node, intr.flag_pipe);
	free_null((void **)&(exe.cmd_path));
	free_null((void **)&(exe.cmd_opts));
	return (status);
}

static int	scan_btree_pipe(int *fd_in, int fd_out, t_ast *node, int flag_pipe)
{
	int		fd_pipe[2];
	int		status;
	int		fd_in_changed;
	t_intr	intr;

	fd_in_changed = *fd_in;
	if (node->data != NULL && node->data->type == PIPE)
	{
		scan_btree_pipe(&fd_in_changed, fd_out, node->left, flag_pipe + 2);
		status = scan_btree_pipe
			(&fd_in_changed, fd_out, node->right, flag_pipe + 1);
		if (flag_pipe > 1)
			*fd_in = fd_in_changed;
	}
	else
	{
		init_intr(&intr, flag_pipe);
		if (make_pipe(fd_pipe, &intr, fd_in, &fd_out) != 0)
			return (1);
		status = scan_simple_cmd(fd_in_changed, fd_out, node, intr);
	}
	return (status);
}

int	execute_ast(t_ast *ast)
{
	int		val;
	int		std_in;

	if (sig_forwarding_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	std_in = STDIN_FILENO;
	val = scan_btree_pipe(&std_in, STDOUT_FILENO, ast, 0);
	while (wait(NULL) > 0)
		;
	minishell_unlink();
	if (sig_interactive_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	return (val);
}
