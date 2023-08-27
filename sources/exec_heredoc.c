/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:24:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/27 19:30:42 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_temporary_name10(char *namespace, char *name, int size_space)
{
	static char	name_lotate;

	if (size_space < ft_strlen(name) + 1)
		return (NULL);
	ft_bzero(namespace, size_space);
	ft_memcpy(namespace, name, ft_strlen(name));
	if (name_lotate < '0' || '9' < name_lotate)
		name_lotate = '0';
	namespace[ft_strlen(name)] = name_lotate++;
	return (namespace);
}

static int	here_doc_expand(char *filename_in, size_t len_here)
{
	int		fd_in;
	int		fd_out;
	int		status;
	char	filename_out[15];

	fd_in = STDIN_FILENO;
	if (ft_open_file(filename_in, LESS, &fd_in) == 1)
		perror_wrap("heredoc expand", 1);
	fd_out = STDOUT_FILENO;
	if (ft_open_file(get_temporary_name10
			(filename_out, ".TMPminishell", 15), GREAT, &fd_out) == 1)
		return (1);
	status = put_expanded_file_fd(fd_in, len_here, fd_out);
	if (close(fd_out) == -1)
		perror_wrap("close: here_doc expand", 1);
	if (status == 1)
		return (status);
	return (print_error(status));
}

static void	putstr_to_fd(char *line, int *fd)
{
	if (*line == '\0')
		ft_putstr_fd("\n", *fd);
	else
		ft_putendl_fd(line, *fd);
}

static int	ft_readline(int *fd_tmphere, char *delimiter, char *filename)
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
			if (close(*fd_tmphere) == -1)
				exit(perror_wrap("readline", 1));
			break ;
		}
		len += ft_strlen(line) + 1;
		putstr_to_fd(line, fd_tmphere);
		free(line);
	}
	if (here_doc_expand(filename, len) != 0)
		exit (1);
	exit(0);
}

int	ft_here_doc(char *delimiter, int *fd_in)
{
	int		pid;
	int		status;
	char	filename1[15];

	if (sig_heredoc_parent_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	if (ft_open_file(get_temporary_name10
			(filename1, ".TMPminishell", 15), GREAT, fd_in) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror_wrap("here_doc fork", 1));
	if (pid == 0)
		ft_readline(fd_in, delimiter, filename1);
	else
	{
		if (waitpid(pid, &status, 0) == -1 || sig_forwarding_mode() != 0)
			return (perror_wrap("here_doc", 1));
		if (ft_open_file(get_temporary_name10
				(filename1, ".TMPminishell", 15), LESS, fd_in) == 1)
			return (1);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
