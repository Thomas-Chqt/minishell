/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_scan_btree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:54:41 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/03 11:05:00 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_readline(char fd_pipe[2], char *delimiter)
{
	char	*line;

	if (close(fd_pipe[0]) == -1)
		exit(ft_print_perror("Error. Fail to close pipe.\n"));
	if (dup2(fd_pipe[1], 1) == -1)
		exit(ft_print_perror("Error. Fail to dup2.\n"));
	if (close(fd_pipe[1]) == -1)
		exit(ft_print_perror("Error. Fail to close pipe.\n"));
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
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

int	ft_here_doc(char *delimiter)
{
	int		fd_pipe[2];
	int		pid;
	char	*line;

	if (pipe(fd_pipe) == -1)
		exit(ft_print_perror("Error. Fail to create pipe.\n"));
	pid = fork();
	if (pid == -1)
		exit(ft_print_perror("Error. Fail to fork.\n"));
	if (pid == 0)
		ft_readline(fd_pipe, delimiter);
	else
	{
		waitpid(pid, NULL, 0);//wait for child process
		if (close(fd_pipe[1]) == -1)
			exit(ft_print_perror("Error. Fail to close pipe.\n"));
	}
	return (fd_pipe[0]);
}

int	scan_btree_fd(t_dexec *dexec, t_tree *node)
{
	if (node == NULL)
		return (0);
	if (node->type == LESS)
		dexec->fd_in = ft_open_file(node->left->data, LESS);
	else if (node->type == GREAT)
		dexec->fd_out = ft_open_file(node->left->data, GREAT);
	else if (node->type == DGREAT)
		dexec->fd_out = ft_open_file(node->left->data, DGREAT);
	else if (node->type == DLESS)
		dexec->fd_in = ft_here_doc(node->left->data);
	scan_btree_fd(dexec, node->right);
	return (0);
}

int	scan_btree_cmd(int fd_in, int fd_out, t_tree *node)
{
	t_dexec	dexec;

	if (node == NULL)
		return (0);
	dexec.fd_in = fd_in;
	dexec.fd_out = fd_out;
	scan_btree_fd(&dexec, node->left);
	if (node->type == NODE_CMD)
	{
		dexec.cmd_opts = //joint cmd & opts to char** matrix, end with NULL;
		if (dexec.cmd_opts == NULL)
			exit(ft_mes_error("Error. Fail allocate memory.\n"));
		ft_exec_fork(path, prog, cmd_opts, envp, &dexec);//Draft version
	}
	return (0);
}

//first call: scan_btree_pipe(0, 1, node);
int	scan_btree_pipe(int fd_in, int fd_out, t_tree *node)
{
	int	fd_pipe[2];

	if (node == NULL)
		return (0);
	if (node->type == NODE_PIPE)
	{
		if (pipe(fd_pipe) == -1)
			exit(ft_print_perror("Error. Fail to create pipe.\n"));
		if (scan_btree(fd_in, fd_pipe[1], node->left) == 1)
			return (1);
		if (close(fd_pipe[1]) == -1)
			exit(ft_print_perror("Error. Fail to close pipe.\n"));
		if (scan_btree(fd_pipe[0], fd_out, node->right) == 1)
			return (1);
	}
	else
	{
		scan_btree_cmd(fd_in, fd_out, node);
	}
	return (0);
}