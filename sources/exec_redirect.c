/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:21:58 by hotph             #+#    #+#             */
/*   Updated: 2023/08/28 16:39:11 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_open_file(char *file_redirect, int flag_redirect, int *fd_io)
{
	int	fd;

	if (flag_redirect == GREAT)
		fd = open(file_redirect, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (flag_redirect == DGREAT)
		fd = open(file_redirect, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(file_redirect, O_RDONLY);
	if (fd == -1)
		return (printf_error_msg("%s: %s",
				(char *[2]){file_redirect, strerror(errno)}, EX_FILE_OPEN_ERR));
	else
	{
		if (*fd_io != fd && *fd_io != STDIN_FILENO && *fd_io != STDOUT_FILENO)
		{
			if (close(*fd_io) == -1)
				return (perror_wrap("open_file close", 1));
		}
		*fd_io = fd;
		return (0);
	}
}

int	scan_btree_io(t_exe *exe, t_ast *node)
{
	int	status;

	status = 0;
	if (node == NULL)
		return (0);
	if (node->data->type == LESS)
		status
			= ft_open_file(node->left->data->data, LESS, &(exe->fd_in));
	else if (node->data->type == GREAT)
		status
			= ft_open_file(node->left->data->data, GREAT, &(exe->fd_out));
	else if (node->data->type == DGREAT)
		status
			= ft_open_file(node->left->data->data, DGREAT, &(exe->fd_out));
	else if (node->data->type == DLESS)
		status
			= ft_here_doc(node->left->data->data, &(exe->fd_in));
	if (status != 0)
		return (status);
	return (scan_btree_io(exe, node->right));
}
