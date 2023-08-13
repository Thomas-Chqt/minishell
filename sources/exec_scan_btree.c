/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scan_btree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:54:41 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/13 12:00:02 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_open_file(char *file_redirect, int flag_redirect, int fd_io)
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
		exit(minishell_error(file_redirect, EX_FILE_OPEN_ERR, NULL));
	else
	{
		if (fd_io != fd && fd_io != STDIN_FILENO && fd_io != STDOUT_FILENO)
		{
			if (close(fd_io) == -1)
				exit(ft_print_perror("Error. Fail to close.\n"));
		}
	}
	return (fd);
}

void	scan_btree_fd(t_dexec *dexec, t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->data->type == LESS)
		dexec->fd_in
			= ft_open_file(node->left->data->data, LESS, dexec->fd_in);
	else if (node->data->type == GREAT)
		dexec->fd_out
			= ft_open_file(node->left->data->data, GREAT, dexec->fd_out);
	else if (node->data->type == DGREAT)
		dexec->fd_out
			= ft_open_file(node->left->data->data, DGREAT, dexec->fd_out);
	else if (node->data->type == DLESS)
		dexec->fd_in
			= ft_here_doc(node->left->data->data, dexec->fd_in);
	scan_btree_fd(dexec, node->right);
}

static int	scan_btree_cmd(int fd_in, int fd_out, t_ast *node, int flag)
{
	t_dexec	dexec;
	int		pid;
	int		status;

	if (node == NULL)
		return (0);
	dexec.fd_in = fd_in;
	dexec.fd_out = fd_out;
	pid = fork();
	if (pid == -1)
		return (ft_print_perror("Error. Fail to fork.\n"));
	else if (pid == 0)
		ft_exec_forked(&dexec, node);
	else
	{
		if (flag <= 1)
		{
			if (waitpid(pid, &status, 0) == -1)
				return (ft_print_perror("Error. Fail to wait.\n"));
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}
	return (0);
}

int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node, int flag)
{
	int	fd_pipe[2];
	int	exit_status;

	exit_status = 0;
	if (node->data != NULL && node->data->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
			return (ft_print_perror("Error. Fail to create pipe.\n"));
		scan_btree_pipe(fd_in, fd_pipe[1], node->left, flag + 2);
		if (close(fd_pipe[1]) == -1)
			return (ft_print_perror("Error. Fail to close pipe[1].\n"));
		exit_status = scan_btree_pipe(fd_pipe[0], fd_out, node->right, flag + 1);
	}
	else
		exit_status = scan_btree_cmd(fd_in, fd_out, node, flag);
	if (node->data->type == PIPE && close(fd_pipe[0]) == -1)
		return (ft_print_perror("Error. Fail to close pipe[0]_scanpipe.\n"));
	if (flag == 0 || flag == 1)
		return (exit_status);
	return (0);
}
