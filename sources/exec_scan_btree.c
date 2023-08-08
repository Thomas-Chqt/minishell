/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scan_btree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:54:41 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/08 15:09:59 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_readline(int fd_pipe[2], char *delimiter)
{
	char	*line;

	if (close(fd_pipe[0]) == -1)
		exit(ft_print_perror("Error. Fail to close pipe[0]_readline\n"));
	if (dup2(fd_pipe[1], 1) == -1)
		exit(ft_print_perror("Error. Fail to dup2_pipi[1].\n"));
	if (close(fd_pipe[1]) == -1)
		exit(ft_print_perror("Error. Fail to close pipe[1].\n"));
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = readline("");
		if (line == NULL)
			break ;
		if (str_cmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
	}
	exit(0);
}

int	ft_here_doc(char *delimiter, int fd_in)
{
	int		fd_pipe[2];
	int		pid;
	char	*line;

	if (fd_in > 0)
	{
		if (close(fd_in) == -1)
			exit(ft_print_perror("Error. Fail to close fd_in.\n"));
	}
	if (pipe(fd_pipe) == -1)
		exit(ft_print_perror("Error. Fail to create pipe.\n"));
	pid = fork();
	if (pid == -1)
		exit(ft_print_perror("Error. Fail to fork.\n"));
	if (pid == 0)
		ft_readline(fd_pipe, delimiter);
	else
	{
		waitpid(pid, NULL, 0);
		if (close(fd_pipe[1]) == -1)
			exit(ft_print_perror("Error. Fail to close pipe[1].\n"));
	}
	return (fd_pipe[0]);
}

int	scan_btree_fd(t_dexec *dexec, t_ast *node)
{
	if (node == NULL)
		return (0);
	if (node->data->type == LESS)
		dexec->fd_in = ft_open_file(node->left->data->data, LESS, dexec->fd_in);
	else if (node->data->type == GREAT)
		dexec->fd_out = ft_open_file(node->left->data->data, GREAT, dexec->fd_out);
	else if (node->data->type == DGREAT)
		dexec->fd_out = ft_open_file(node->left->data->data, DGREAT, dexec->fd_out);
	else if (node->data->type == DLESS)
		dexec->fd_in = ft_here_doc(node->left->data->data, dexec->fd_in);
	scan_btree_fd(dexec, node->right);
	return (0);
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
	if (node->data->type == TEXT)
	{
		pid = fork();
		if (pid == -1)
			exit(ft_print_perror("Error. Fail to fork.\n"));
		else if (pid == 0)
			ft_exec_forked(&dexec, node);
		else
		{
			if (wait(&status) == -1)
				exit(ft_print_perror("Error. Fail to wait.\n"));
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}
	return (0);
}

int	scan_btree_pipe(int fd_in, int fd_out, t_ast *node)
{
	int	fd_pipe[2];
	int	exit_status;

	if (node == NULL)
		return (0);
	exit_status = 0;
	if (node->data->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
			exit(ft_print_perror("Error. Fail to create pipe.\n"));
		if (scan_btree_pipe(fd_in, fd_pipe[1], node->left) == 1)
			return (1);
		if (close(fd_pipe[1]) == -1)
			exit(ft_print_perror("Error. Fail to close pipe[1].\n"));
		if (scan_btree_pipe(fd_pipe[0], fd_out, node->right) == 1)
			return (1);
	}
	else
	{
		exit_status = scan_btree_cmd(fd_in, fd_out, node);
		if (node->data->type == PIPE && close(fd_pipe[0]) == -1)
			exit(ft_print_perror("Error. Fail to close pipe[0]_scanpipe.\n"));
	}
	return (exit_status);
}
