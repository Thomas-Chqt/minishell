/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:21:58 by hotph             #+#    #+#             */
/*   Updated: 2023/08/14 12:10:28 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_readline(int fd_pipe[2], char *delimiter)
{
	char	*line;

	if (close(fd_pipe[0]) == -1)
		exit(perror_wrap("readline pipe[0]", 1));
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = readline("");
		if (line == NULL)
			break ;
		if (str_cmp(line, delimiter) == 0)
		{
			free(line);
			if (close(fd_pipe[1]) == -1)
				exit(perror_wrap("readline pipe[1]", 1));
			break ;
		}
		ft_putstr_fd(line, fd_pipe[1]);
		ft_putstr_fd("\n", fd_pipe[1]);
		free(line);
	}
	exit(0);
}

static int	ft_here_doc(char *delimiter, int *fd_in)
{
	int		fd_pipe[2];
	int		pid;
	int		status;

	if (*fd_in > 2)
	{
		if (close(*fd_in) == -1)
			return (perror_wrap("here_doc close", 1));
	}
	if (pipe(fd_pipe) == -1)
		return (perror_wrap("heredoc create", 1));
	*fd_in = fd_pipe[0];
	pid = fork();
	if (pid == -1)
		return (perror_wrap("here_doc fork", 1));
	if (pid == 0)
		ft_readline(fd_pipe, delimiter);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (perror_wrap("here_doc waitpid", 1));
		if (close(fd_pipe[1]) == -1)
			return (perror_wrap("here_doc fd_pipe[1]", 1));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

static int	ft_open_file(char *file_redirect, int flag_redirect, int *fd_io)
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
		return (exec_error(file_redirect, EX_FILE_OPEN_ERR, NULL));
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

int	scan_btree_io(t_dexec *dexec, t_ast *node)
{
	int	status;

	if (node == NULL)
		return (0);
	if (node->data->type == LESS)
		status
			= ft_open_file(node->left->data->data, LESS, &(dexec->fd_in));
	else if (node->data->type == GREAT)
		status
			= ft_open_file(node->left->data->data, GREAT, &(dexec->fd_out));
	else if (node->data->type == DGREAT)
		status
			= ft_open_file(node->left->data->data, DGREAT, &(dexec->fd_out));
	else if (node->data->type == DLESS)
		status
			= ft_here_doc(node->left->data->data, &(dexec->fd_in));
	if (status != 0)
		return (status);
	return (scan_btree_io(dexec, node->right));
}
