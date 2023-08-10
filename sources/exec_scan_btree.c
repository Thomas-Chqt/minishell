/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scan_btree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:54:41 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/09 18:10:14 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	scan_btree_fd(t_dexec *dexec, t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->data->type == LESS)
		dexec->fd_in = ft_open_file(node->left->data->data, LESS, dexec->fd_in);
	else if (node->data->type == GREAT)
		dexec->fd_out = ft_open_file(node->left->data->data, GREAT, dexec->fd_out);
	else if (node->data->type == DGREAT)
		dexec->fd_out = ft_open_file(node->left->data->data, DGREAT, dexec->fd_out);
	else if (node->data->type == DLESS)
		dexec->fd_in = ft_here_doc(node->left->data->data, dexec->fd_in);
	scan_btree_fd(dexec, node->right);
}

static int	scan_btree_cmd(int fd_in, int fd_out, t_ast *node)
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
		exit(ft_print_perror("Error. Fail to fork.\n"));
	else if (pid == 0)
		ft_exec_forked(&dexec, node);
	else
	{
		if (wait(&status) == -1)
			return (ft_print_perror("Error. Fail to wait.\n"));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node)
{
	int	fd_pipe[2];
	int	exit_status;

	exit_status = 0;
	if (node->data != NULL && node->data->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
			return (ft_print_perror("Error. Fail to create pipe.\n"));
		if (scan_btree_pipe(fd_in, fd_pipe[1], node->left) == 1)
			return (1);
		if (close(fd_pipe[1]) == -1)
			return (ft_print_perror("Error. Fail to close pipe[1].\n"));
		if (scan_btree_pipe(fd_pipe[0], fd_out, node->right) == 1)
			return (1);
	}
	else
		exit_status = scan_btree_cmd(fd_in, fd_out, node);
	if (node->data->type == PIPE && close(fd_pipe[0]) == -1)
		return (ft_print_perror("Error. Fail to close pipe[0]_scanpipe.\n"));
	return (exit_status);
}
