/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:16:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/27 14:33:27 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "environment.h"

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

static int	set_env_all(t_ast **node, t_ast **current)
{
	int	status;

	status = 0;
	*current = *node;
	while (*current != NULL)
	{
		status = set_env_single_str((*current)->data->data, 0);
		if (status == MALLOC_ERROR)
			return (print_error(MALLOC_ERROR));
		*current = (*current)->right;
	}
	return (status);
}

int	skip_if_environment(t_ast **node)
{
	int		status;
	t_ast	*current;

	status = 1;
	current = *node;
	while (current != NULL)
	{
		status = is_valid_keyval(current->data->data);
		if (status != 0)
		{
			status = 1;
			break ;
		}
		current = current->right;
	}
	if (status == 0)
		status = set_env_all(node, &current);
	*node = current;
	return (status);
}

void	minishell_unlink(void)
{
	int		i;
	char	filename[15];

	i = 10;
	while (i--)
		unlink(get_temporary_name10(filename, ".TMPminishell", 15));
}
