/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:17:56 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/17 16:27:12 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "exec.h"

void	init_dexec(int fd_in, int fd_out, t_dexec *dexec, t_intr *intr)
{
	dexec->matrix_envpath = NULL;
	dexec->cmd_path = NULL;
	dexec->cmd_opts = NULL;
	dexec->fd_in = fd_in;
	dexec->fd_out = fd_out;
	dexec->flag_pipe_close = 0;
	dexec->pipe = intr->pipe;
	dexec->flag_pipe = intr->flag_pipe;
	dexec->flag_builtin = -1;
}

int	cmd_only_redirection(t_dexec *dexec, int status)
{
	if (fd_close(dexec->fd_in, dexec->fd_out) != 0)
		return (perror_wrap("scan cmd fd_close", 1));
	return (status);
}

static int	scan_simple_cmd(int fd_in, int fd_out, t_ast *node, t_intr intr)
{
	t_dexec	dexec;
	int		status;

	init_dexec(fd_in, fd_out, &dexec, &intr);
	status = scan_btree_io(&dexec, node->left);
	if (status != 0 || node->data == NULL)
		return (cmd_only_redirection(&dexec, status));
	if (fd_out == dexec.fd_out && fd_out != STDOUT_FILENO)
		dexec.flag_pipe_close = 1;
	status = scan_path_prog(&dexec, node);
	if (status != 0)
	{
		free_null((void **)&(dexec.cmd_path));
		return (status);
	}
	status = exec_do(&dexec, node, intr.flag_wait);
	free_null((void **)&(dexec.cmd_path));
	free_null((void **)&(dexec.cmd_opts));
	return (status);
}

static int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node, t_intr intr)
{
	int	fd_pipe[2];
	int	status;

	if (node->data != NULL && node->data->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
			return (perror_wrap("scan_pipe", 1));
		scan_btree_pipe(fd_in, fd_pipe[1], node->left,
			(t_intr){fd_pipe, intr.flag_wait + 2, 1});
		status = scan_btree_pipe(fd_pipe[0], fd_out, node->right,
				(t_intr){intr.pipe, intr.flag_wait + 1, 1});
	}
	else
		status = scan_simple_cmd(fd_in, fd_out, node, intr);
	return (status);
}

void	execute_ast(t_ast *ast)
{
	int		val;
	t_intr	intr;

	if (sig_forwarding_mode() != 0)
		return ;
	intr = (t_intr){NULL, 0, 0};
	val = scan_btree_pipe(STDIN_FILENO, STDOUT_FILENO, ast, intr);
	while (wait(NULL) > 0)
		;
	set_last_error(val);
	if (sig_interactive_mode() != 0)
		return ;
}
