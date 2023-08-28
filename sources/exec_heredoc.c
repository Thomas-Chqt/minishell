/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:24:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/28 11:08:20 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	here_doc_expand(char *filename_read, size_t len_here)
{
	int		fd_in;
	int		fd_out;
	int		status;
	char	filename_write[15];

	fd_in = STDIN_FILENO;
	if (ft_open_file(filename_read, LESS, &fd_in) == 1)
		perror_wrap("heredoc expand", 1);
	fd_out = STDOUT_FILENO;
	if (ft_open_file(get_temporary_name10
			(filename_write, ".TMPminishell", 15), GREAT, &fd_out) == 1)
		return (1);
	status = put_expanded_file_fd(fd_in, len_here, fd_out);
	if (close(fd_out) == -1)
		perror_wrap("close: here_doc expand", 1);
	if (status == 1)
		return (status);
	return (print_error(status));
}

static int	ft_readline(int *fd_out, char *delimiter, char *filename)
{
	char	*line;
	size_t	len;

	len = 0;
	if (sig_heredoc_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (str_cmp(line, delimiter) == 0)
		{
			free(line);
			if (close(*fd_out) == -1)
				exit(perror_wrap("readline", 1));
			break ;
		}
		len += ft_strlen(line) + 1;
		putstr_to_fd(line, fd_out);
		free(line);
	}
	if (here_doc_expand(filename, len) != 0)
		exit (1);
	exit(0);
}

static int	at_parent(char *filename_read, int pid, int *fd_in)
{
	int		status;

	if (waitpid(pid, &status, 0) == -1 || sig_forwarding_mode() != 0)
		return (perror_wrap("here_doc", 1));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (ft_open_file(get_temporary_name10
			(filename_read, ".TMPminishell", 15), LESS, fd_in) == 1)
		return (1);
	return (WEXITSTATUS(status));
}

int	ft_here_doc(char *delimiter, int *fd_in)
{
	char	filename_write[15];
	int		pid;

	if (sig_heredoc_parent_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	if (ft_open_file(get_temporary_name10
			(filename_write, ".TMPminishell", 15), GREAT, fd_in) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror_wrap("here_doc fork", 1));
	if (pid == 0)
		ft_readline(fd_in, delimiter, filename_write);
	else
		return (at_parent(filename_write, pid, fd_in));
	return (0);
}
