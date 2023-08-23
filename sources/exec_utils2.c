/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:16:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/24 14:28:40 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "environment.h"

void	init_intr(t_intr *intr, int flag_pipe)
{
	intr->flag_pipe = flag_pipe;
	intr->pipe = NULL;
}

void	init_exe(int fd_in, int fd_out, t_exe *exe, t_intr *intr)
{
	exe->matrix_envpath = NULL;
	exe->cmd_path = NULL;
	exe->cmd_opts = NULL;
	exe->fd_in = fd_in;
	exe->fd_out = fd_out;
	exe->flag_pipe_close = 0;
	exe->pipe = intr->pipe;
	exe->flag_pipe = intr->flag_pipe;
	exe->flag_builtin = -1;
}

int	end_with_fd_close(t_exe *exe, int status)
{
	if (fd_close(exe->fd_in, exe->fd_out) != 0)
		return (perror_wrap("scan cmd fd_close", 1));
	return (status);
}

int	scan_environment(t_ast *node)
{
	if (node->data != NULL && node->data->type == TEXT)
	{
		if (is_valid_keyval(node->data->data) == 0)
			return (1);
	}
	return (0);
}
