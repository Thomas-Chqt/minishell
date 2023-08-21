/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:16:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/21 19:08:05 by sotanaka         ###   ########.fr       */
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
